#include "main.h"

#include <typeinfo>
#include <QSignalMapper>

#include "../models/p_core.h"
#include "c_mainwindow.h"
#include "../views/v_mainwindow.h"
#include "../views/v_littlenote.h"
#include "ui_v_mainwindow.h"
#include "ui_v_articleform.h"
#include "ui_v_multimediaform.h"
#include "ui_v_taskform.h"
#include "ui_v_multiplenotes.h"
#include "ui_v_multiplerelation.h"

C_Mainwindow::C_Mainwindow(QApplication *q) {

    // Initialisation des models et de la view
    qapp = q;
    app = new PluriNotes;

    view = new V_Mainwindow(0,this);

    refreshActiveNotes();
    refreshTask();
    createActions();
}

void C_Mainwindow::createActions()
{
    view->getUi()->actionShow_Asc_Desc_View->setChecked(true);

    view->connect(view->getUi()->actionQuit, SIGNAL(triggered()), qapp, SLOT(quit()) );
    view->connect(view->getUi()->actionArticle, SIGNAL(triggered()), view, SLOT(openNewArticle()));
    view->connect(view->getUi()->actionMultimedia,SIGNAL(triggered()),view,SLOT(openNewMultimedia()));
    view->connect(view->getUi()->actionTask,SIGNAL(triggered()),view,SLOT(openNewTask()));
    view->connect(view->getUi()->actionRelation,SIGNAL(triggered()),view,SLOT(openNewRelation()));
    view->connect(view->getUi()->actionShow_Asc_Desc_View,SIGNAL(triggered()),view,SLOT(toggleAscDescView()));
    view->connect(view->getUi()->actionShow_Relations_View,SIGNAL(triggered()),view,SLOT(toggleRelationsView()));
}

void C_Mainwindow::refreshActiveNotes() {
    std::vector<Note*> *notes = app->getActiveNotesManager()->getTab();
    unsigned int row = 0;
    unsigned int column = 0;

    // Remise à 0 du GridLayout
    QLayoutItem* item;
    while ( ( item = view->getActiveNotes()->getGridLayout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    QSignalMapper* signalMapper = new QSignalMapper(view);
    view->connect(signalMapper, SIGNAL(mapped(QString)),view, SLOT(refreshCentralNote(QString)));

    for(unsigned int i = 0; i < notes->size(); i++) {
        Note* note = notes->at(i);

        V_Littlenote* ln;

        if( typeid(*note) == typeid(Article) ) {
            Article* a = new Article( dynamic_cast<Article&>(*note) );
            ln = new V_Littlenote(this->getView()->getActiveNotes()->getContainer(),a->getId(),article);
            view->getActiveNotes()->getGridLayout()->addWidget(ln,row,column);

            if( column != 0 && column % 1 == 0 )
            {
                row++;
                column=0;
            } else column++;

            signalMapper->setMapping(ln, note->getId());
            view->connect(ln, SIGNAL(clicked()), signalMapper, SLOT(map()));
        }

        if( typeid(*note) == typeid(Multimedia) ) {
            Multimedia* a = new Multimedia( dynamic_cast<Multimedia&>(*note) );
            ln = new V_Littlenote(this->getView()->getActiveNotes()->getContainer(),a->getId(),multimedia);
            view->getActiveNotes()->getGridLayout()->addWidget(ln,row,column);

            if( column != 0 && column % 1 == 0 )
            {
                row++;
                column=0;
            } else column++;

            signalMapper->setMapping(ln, note->getId());
            view->connect(ln, SIGNAL(clicked()), signalMapper, SLOT(map()));
        }
    }
}

void C_Mainwindow::refreshTask()
{
    std::vector<Note*> *notes = app->getActiveNotesManager()->getTab();
    unsigned int row = 0;

    // Remise à 0 du GridLayout
    QLayoutItem* item;
    while ( ( item = view->getTasks()->getGridLayout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    QSignalMapper* signalMapper = new QSignalMapper(view);
    view->connect(signalMapper, SIGNAL(mapped(QString)),view, SLOT(refreshCentralNote(QString)));

    std::vector<Note*> *tasks = new std::vector<Note*>;;

    //Recupération de toutes les taches
    for (unsigned int i = 0; i < notes->size(); i++)
    {
        Note* note = notes->at(i);

        if(typeid(*note) == typeid(Task))
        {
            tasks->push_back(note);
        }
    }

    //tri des taches

    for (unsigned int i = 0; i < tasks->size(); i++)
    {
        Note* task = tasks->at(i);
        Task* a = new Task( dynamic_cast<Task&>(*task) );

        unsigned int max, indice = 0;

        Note* tmp;

        //initialisation
        max = a->getPriority();
        indice = i;

        for(unsigned j = i; j < tasks->size(); j++)
        {
            Note* task2 = tasks->at(j);
            Task* b = new Task( dynamic_cast<Task&>(*task2) );

            //recupération du maximum
            if( max < b->getPriority())
            {
                max = b->getPriority();
                indice = j;
            }
         }
        if(i!= indice)
        {
            tmp = tasks->at(i);
            tasks->at(i) = tasks->at(indice);
            tasks->at(indice) = tmp;
        }
    }

    for(unsigned int i = 0; i < tasks->size(); i++) {
        Note* task = tasks->at(i);
        V_Littletask* la;
        Task* a = new Task( dynamic_cast<Task&>(*task) );

        la = new V_Littletask(this->getView()->getTasks()->getContainer(),a->getTitle(),a->getDeadline().toString(),a->getPriority());
        view->getTasks()->getGridLayout()->addWidget(la,row,0);

        row++;

        signalMapper->setMapping(la, task->getId());
        view->connect(la, SIGNAL(clicked()), signalMapper, SLOT(map()));
    }
}

void C_Mainwindow::saveNewArticle(Article *a) {
    app->getActiveNotesManager()->getTab()->push_back(a);
    app->getXMLManager()->insertIntoArticle(a);
    refreshActiveNotes();
}

void C_Mainwindow::saveNewMultimedia(Multimedia *m) {

    // Déplacer le fichier dans le dossier ressources
    QFile *file = new QFile(m->getFileName());
    QFileInfo fileInfo(file->fileName());
    QDir dirToRessources(QDir::currentPath());
    dirToRessources.cd("../plurinotes/ressources/");

    QString from(m->getFileName());
    QString to(dirToRessources.absolutePath()+ QDir::separator() + m->getId() + "." + fileInfo.completeSuffix());
    QFile::copy(from,to);

    m->setFileName(m->getId() + "." + fileInfo.completeSuffix());

    app->getActiveNotesManager()->getTab()->push_back(m);
    app->getXMLManager()->insertIntoMultimedia(m);
    refreshActiveNotes();
}

void C_Mainwindow::saveNewTask(Task *t) {

    app->getActiveNotesManager()->getTab()->push_back(t);
    app->getXMLManager()->insertIntoTask(t);
    refreshTask();
}

void C_Mainwindow::saveNewRelation(Relation *r) {
    app->getRelationManager()->getTab()->push_back(r);
    this->getView()->getRelationView()->refreshRelation();


}

void C_Mainwindow::addCouple(Couple *c,QString rId) {
    Relation* relation = app->getRelationByID(rId);

    if(relation->getOriented() == false)
    {
        QString id = c->generateCoupleId(c->getY(),c->getX());

        Couple* couple = new Couple(
                    c->getLabel(),
                    c->getY(),
                    c->getX()
                    );
        relation->getCouples()->push_back(couple);
    }

    relation->getCouples()->push_back(c);
    this->getView()->getRelationView()->refreshListCouple(rId);
}

void C_Mainwindow::editArticle(QString id,Article* newV)
{
    Article* article = &(dynamic_cast<Article&>(*(app->getNoteByID(id))));

    if( article->getText() != newV->getText() || article->getTitle() != newV->getTitle() ) {
        app->getXMLManager()->updateArticle(article,newV);
        app->reloadFromDatabase();
        view->refreshCentralNote(id);
    }
}

void C_Mainwindow::editMultimedia(QString id,Multimedia* newV)
{
    Multimedia* multimedia = &(dynamic_cast<Multimedia&>(*(app->getNoteByID(id))));

    if( multimedia->getTitle() != newV->getTitle() || multimedia->getDescription() != newV->getDescription()) {
        app->getXMLManager()->updateMultimedia(multimedia,newV);
        app->reloadFromDatabase();
        view->refreshCentralNote(id);
    }
}

void C_Mainwindow::editTask(QString id,Task* newV)
{
    Task* task = &(dynamic_cast<Task&>(*(app->getNoteByID(id))));
    if( task->getTitle() != newV->getTitle() || task->getAction() != newV->getAction() || task->getPriority() != newV->getPriority() || task->getDeadline() != newV->getDeadline() || task->getStatus() != newV->getStatus()) {
        app->getXMLManager()->updateTask(task,newV);
        app->reloadFromDatabase();
        view->refreshCentralNote(id);
        refreshTask();
    }
}

void C_Mainwindow::editRelation(Relation* r)
{
    Relation* relation = app->getRelationByID(r->getId());
    relation->setTitle(r->getTitle());
    relation->setDesc(r->getDesc());
    relation->setOriented(r->getOriented());
}

void C_Mainwindow::editCouple(Couple* c,QString RId)
{
    Relation* relation = app->getRelationByID(RId);

    Couple* couple = app->getCoupleByID(c->getId(),relation);

    couple->setLabel(c->getLabel());
    couple->setX(c->getX());
    couple->setY(c->getY());


}

void C_Mainwindow::deleteByID(QString id) {

    // WIP Suppression en base
    Note* note = app->getNoteByID(id);

    if( typeid(*note) == typeid(Article) ) {
        Article* article = new Article(dynamic_cast<Article&>(*note));
        app->getXMLManager()->deleteFromArticle(article);
    }

    if( typeid(*note) == typeid(Multimedia) ) {
        Multimedia* multimedia = new Multimedia(dynamic_cast<Multimedia&>(*note));
        app->getXMLManager()->deleteFromMultimedia(multimedia);
        // TODO Suppression du fichier pour les multimédias

        QFile file(multimedia->getFileName());
        QFileInfo fileInfo(file.fileName());
        QDir dirToRessources(QDir::currentPath());
        dirToRessources.cd("../plurinotes/ressources/");
        QString filePath = dirToRessources.absolutePath()+ QDir::separator() + multimedia->getId() + "." + fileInfo.completeSuffix();
        QFile completeFile(filePath);
        completeFile.remove();
    }

    if( typeid(*note) == typeid(Task) ) {
        Task* task = new Task(dynamic_cast<Task&>(*note));
        app->getXMLManager()->deleteFromTask(task);
    }

    //Suppression dans les notes actives (côté vue)
    for(unsigned int i = 0; i < app->getActiveNotesManager()->getTab()->size() ; i++ )
    {
        note = app->getActiveNotesManager()->getTab()->at(i);
        if( note->getId() == id ) app->getActiveNotesManager()->getTab()->erase(app->getActiveNotesManager()->getTab()->begin() + i);
    }

    refreshActiveNotes();
    refreshTask();
    view->setEmptyCentralNote();


}

void C_Mainwindow::restoreNoteVersion(QString noteID, QString numVersion) {
    // XML :
    // - Update de l'état actuel avec la version voulue
    // - Suppression de toutes les versions
    Note *n = app->getNoteByID(noteID);
    Version *v = app->getNoteVersionByID(noteID,numVersion);

    app->getXMLManager()->restoreNoteVersion(n,v);

    //Suppression dans les notes actives (côté vue)
    for(unsigned int i = 0; i < app->getActiveNotesManager()->getTab()->size() ; i++ ) {
        Note *note = app->getActiveNotesManager()->getTab()->at(i);

        if( note->getId() == n->getId() ) {

            for(unsigned int j = 0; j < note->getVersions()->size() ; j++ ) {
                Version *version = note->getVersions()->at(j);

                if( version->getNumVersion() == v->getNumVersion() ) {

                    if(typeid(*n) == typeid(Article)) {
                        Article *aFromVersion = new Article(dynamic_cast<Article&>(*(version->getState())));
                        Article *article = &(dynamic_cast<Article&>(*(note)));

                        article->setTitle(aFromVersion->getTitle());
                        article->setText(aFromVersion->getText());
                        article->setLastModifOn(QDateTime::currentDateTime());
                    } else if(typeid(*n) == typeid(Multimedia)) {
                        Multimedia *mFromVersion = new Multimedia(dynamic_cast<Multimedia&>(*(version->getState())));
                        Multimedia *multimedia = &(dynamic_cast<Multimedia&>(*(note)));

                        multimedia->setTitle(mFromVersion->getTitle());
                        multimedia->setDesc(mFromVersion->getDescription());
                        multimedia->setLastModifOn(QDateTime::currentDateTime());
                    } else {
                        Task *tFromVersion = new Task(dynamic_cast<Task&>(*(version->getState())));
                        Task *task = &(dynamic_cast<Task&>(*(note)));

                        task->setTitle(tFromVersion->getTitle());
                        task->setAction(tFromVersion->getAction());
                        task->setDeadline(tFromVersion->getDeadline());
                        task->setStatus(tFromVersion->getStatus());
                        task->setPriority(tFromVersion->getPriority());
                        task->setLastModifOn(QDateTime::currentDateTime());
                    }
                }
            }
            note->getVersions()->clear();
        }
    }

    refreshActiveNotes();
    refreshTask();
    view->refreshCentralNote(noteID);
}

void C_Mainwindow::deleteNoteVersion(QString noteID, QString numVersion) {
    // XML :
    // - Suppression de la version voulue et de toutes les versions ultérieures
    Note *n = app->getNoteByID(noteID);
    Version *v = app->getNoteVersionByID(noteID,numVersion);

    app->getXMLManager()->deleteNoteVersion(n,v);

    //Suppression dans les notes actives (côté vue)
    for(unsigned int i = 0; i < app->getActiveNotesManager()->getTab()->size() ; i++ ) {
        Note *note = app->getActiveNotesManager()->getTab()->at(i);

        if( note->getId() == n->getId() ) {

            int index = -1;
            for(unsigned int j = 0; j < note->getVersions()->size() ; j++ ) {
                Version *version = note->getVersions()->at(j);

                if( version->getNumVersion() == v->getNumVersion() ) index = j;
            }

            if(index != -1) note->getVersions()->erase(note->getVersions()->begin() + index, note->getVersions()->end());
        }
    }

    refreshActiveNotes();
    refreshTask();
    view->refreshVersions(noteID);
}
