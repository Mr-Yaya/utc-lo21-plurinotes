#include "p_xml.h"
#include "main.h"

XMLManager::XMLManager(const QString &path ) : QWidget()  {
    dom = new QDomDocument("XMLManagerDom");
    pathToFile = path;
    QFile doc(path);

    if(!doc.open(QIODevice::ReadOnly)) {
         QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre ouvert. Verifiez que le nom est le bon et que le document est bien place");
         return;
    }

    if (!dom->setContent(&doc)) {
        doc.close();
        QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre attribue a l'objet QDomDocument.");
        return;
    }
    doc.close();
}

std::vector<Article*> XMLManager::getAllActiveArticles() const {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement articles = activeNotes.firstChildElement("articles");
    QDomElement article = articles.firstChildElement("article");
    QString createdOn,lastModifOn;

    std::vector<Article*> tab;

    for(;!article.isNull(); article = article.nextSiblingElement("article")) {

        createdOn = article.firstChildElement("createdOn").text();
        lastModifOn = article.firstChildElement("lastModifOn").text();

        Article *a = new Article(
            article.firstChildElement("id").text(),
            article.firstChildElement("title").text(),
            QDateTime::fromString(createdOn),
            QDateTime::fromString(lastModifOn),
            article.firstChildElement("text").text()
        );

        tab.push_back(a);
    }

    return tab;
}

std::vector<Multimedia*> XMLManager::getAllActiveMultimedia() const {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement multimedias = activeNotes.firstChildElement("multimedias");
    QDomElement multimedia = multimedias.firstChildElement("multimedia");
    QString createdOn,lastModifOn;

    std::vector<Multimedia*> tab;

    for(;!multimedia.isNull(); multimedia = multimedia.nextSiblingElement("multimedia")) {

        createdOn = multimedia.firstChildElement("createdOn").text();
        lastModifOn = multimedia.firstChildElement("lastModifOn").text();

        Multimedia *a = new Multimedia(
            multimedia.firstChildElement("id").text(),
            multimedia.firstChildElement("title").text(),
            QDateTime::fromString(createdOn),
            QDateTime::fromString(lastModifOn)
        );

        tab.push_back(a);
    }

    return tab;
}

std::vector<Task*> XMLManager::getAllActiveTasks() const {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement tasks = activeNotes.firstChildElement("tasks");
    QDomElement task = tasks.firstChildElement("task");
    QString tmp;
    QDateTime createdOn,lastModifOn;

    std::vector<Task*> tab;

    for(;!task.isNull(); task = task.nextSiblingElement("task")) {

        //Convertion de Qstring de l'XML en QDateTime

        tmp = task.firstChildElement("createdOn").text();
        createdOn.fromString(tmp,"yyyy:MM:dd hh:mm:ss");
        tmp = task.firstChildElement("lastModifOn").text();
        lastModifOn.fromString(tmp,"yyyy:MM:dd hh:mm:ss");

        Task *a = new Task(
            task.firstChildElement("id").text(),
            task.firstChildElement("title").text(),
            createdOn,
            lastModifOn
        );

        tab.push_back(a);
    }

    return tab;
}

void XMLManager::insertIntoArticle(Article*a) {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement articles = activeNotes.firstChildElement("articles");

    QDomElement newArticle = dom->createElement("article");
        QDomElement aID = dom->createElement("id");
            aID.appendChild(dom->createTextNode(a->getId()));
        QDomElement aTitle = dom->createElement("title");
            aTitle.appendChild(dom->createTextNode(a->getTitle()));
        QDomElement aCreatedOn = dom->createElement("createdOn");
            aCreatedOn.appendChild(dom->createTextNode(a->getCreatedOn().toString()));
        QDomElement aLastModifOn = dom->createElement("lastModifOn");
            aLastModifOn.appendChild(dom->createTextNode(a->getLastModifOn().toString()));
        QDomElement aText = dom->createElement("text");
            aText.appendChild(dom->createTextNode(a->getText()));

    newArticle.appendChild(aID);
    newArticle.appendChild(aTitle);
    newArticle.appendChild(aCreatedOn);
    newArticle.appendChild(aLastModifOn);
    newArticle.appendChild(aText);

    articles.appendChild(newArticle);

    QString newDoc = dom->toString();

    QFile doc(pathToFile);
    if(!doc.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
         QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre ouvert. Verifiez que le nom est le bon et que le document est bien place");
         return;
    }

    QTextStream stream(&doc);

    stream << newDoc;
}

void XMLManager::insertIntoMultimedia(Multimedia*m) {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement multimedias = activeNotes.firstChildElement("multimedias");

    QDomElement newMultimedia = dom->createElement("multimedia");
        QDomElement mID = dom->createElement("id");
            mID.appendChild(dom->createTextNode(m->getId()));
        QDomElement mTitle = dom->createElement("title");
            mTitle.appendChild(dom->createTextNode(m->getTitle()));
        QDomElement mCreatedOn = dom->createElement("createdOn");
            mCreatedOn.appendChild(dom->createTextNode(m->getCreatedOn().toString()));
        QDomElement mLastModifOn = dom->createElement("lastModifOn");
            mLastModifOn.appendChild(dom->createTextNode(m->getLastModifOn().toString()));
        QDomElement mDescription = dom->createElement("description");
            mDescription.appendChild(dom->createTextNode(m->getDescription()));
        QDomElement mFileName = dom->createElement("fileName");
            mFileName.appendChild(dom->createTextNode(m->getFileName()));
        QDomElement mType = dom->createElement("type");
            if(m->getType() == AUDIO ) mType.appendChild(dom->createTextNode("audio"));
            else if(m->getType() == VIDEO ) mType.appendChild(dom->createTextNode("video"));
            else mType.appendChild(dom->createTextNode("picture"));


    newMultimedia.appendChild(mID);
    newMultimedia.appendChild(mTitle);
    newMultimedia.appendChild(mCreatedOn);
    newMultimedia.appendChild(mLastModifOn);
    newMultimedia.appendChild(mDescription);
    newMultimedia.appendChild(mFileName);
    newMultimedia.appendChild(mType);

    multimedias.appendChild(newMultimedia);

    QString newDoc = dom->toString();

    QFile doc(pathToFile);
    if(!doc.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
         QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre ouvert. Verifiez que le nom est le bon et que le document est bien place");
         return;
    }

    QTextStream stream(&doc);

    stream << newDoc;
}

unsigned int XMLManager::getLastId() const {
    unsigned int lastID = 0;
    unsigned int foundID = 0;

    // On cherche dans les notes actives
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");

        // Articles
        QDomElement articles = activeNotes.firstChildElement("articles");
        QDomElement article = articles.firstChildElement("article");
        for(;!article.isNull(); article = article.nextSiblingElement("article")) {
            foundID = article.firstChildElement("id").text().toInt(0,10);
            if(foundID > lastID) lastID = foundID;
        }

        // Multimedia
        QDomElement multimedias = activeNotes.firstChildElement("multimedias");
        QDomElement multimedia = multimedias.firstChildElement("multimedia");
        for(;!multimedia.isNull(); multimedia = multimedia.nextSiblingElement("multimedia")) {
            foundID = multimedia.firstChildElement("id").text().toInt(0,10);
            if(foundID > lastID) lastID = foundID;
        }

        // Tasks
        QDomElement tasks = activeNotes.firstChildElement("tasks");
        QDomElement task = tasks.firstChildElement("task");
        for(;!task.isNull(); task = task.nextSiblingElement("task")) {
            foundID = task.firstChildElement("id").text().toInt(0,10);
            if(foundID > lastID) lastID = foundID;
        }

    // On cherche dans les notes archivées
    QDomElement archivedNotes = root.firstChildElement("archivedNotes");

        // Articles
        articles = archivedNotes.firstChildElement("articles");
        article = articles.firstChildElement("article");
        for(;!article.isNull(); article = article.nextSiblingElement("article")) {
            foundID = article.firstChildElement("id").text().toInt(0,10);
            if(foundID > lastID) lastID = foundID;
        }

        // Multimedia
        multimedias = archivedNotes.firstChildElement("multimedias");
        multimedia = multimedias.firstChildElement("multimedia");
        for(;!multimedia.isNull(); multimedia = multimedia.nextSiblingElement("multimedia")) {
            foundID = multimedia.firstChildElement("id").text().toInt(0,10);
            if(foundID > lastID) lastID = foundID;
        }

        // Tasks
        tasks = archivedNotes.firstChildElement("tasks");
        task = tasks.firstChildElement("task");
        for(;!task.isNull(); task = task.nextSiblingElement("task")) {
            foundID = task.firstChildElement("id").text().toInt(0,10);
            if(foundID > lastID) lastID = foundID;
        }

    return lastID;
}

XMLManager::~XMLManager() {
    doc.close();
}
