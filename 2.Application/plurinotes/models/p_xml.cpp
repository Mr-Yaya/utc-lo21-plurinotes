#include "p_xml.h"

XMLManager::XMLManager(const QString &path ) : QWidget() {
    dom = new QDomDocument("XMLManagerDom");
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
}

std::vector<Article*> XMLManager::getAllActiveArticles() {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement articles = activeNotes.firstChildElement("articles");
    QDomElement article = articles.firstChildElement("article");

    std::vector<Article*> tab;

    for(;!article.isNull(); article = article.nextSiblingElement("article")) {
        Article *a = new Article(
            article.firstChildElement("id").text(),
            article.firstChildElement("title").text(),
            article.firstChildElement("createdOn").text(),
            article.firstChildElement("lastModifOn").text(),
            article.firstChildElement("text").text()
        );

        tab.push_back(a);
    }

    return tab;
}

std::vector<Multimedia*> XMLManager::getAllActiveMultimedia() {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement multimedias = activeNotes.firstChildElement("multimedias");
    QDomElement multimedia = multimedias.firstChildElement("multimedia");

    std::vector<Multimedia*> tab;

    for(;!multimedia.isNull(); multimedia = multimedia.nextSiblingElement("multimedia")) {
        Multimedia *a = new Multimedia(
            multimedia.firstChildElement("id").text(),
            multimedia.firstChildElement("title").text(),
            multimedia.firstChildElement("createdOn").text(),
            multimedia.firstChildElement("lastModifOn").text()
        );

        tab.push_back(a);
    }

    return tab;
}

std::vector<Task*> XMLManager::getAllActiveTasks() {
    QDomElement root = dom->firstChildElement("plurinotes");
    QDomElement activeNotes = root.firstChildElement("activeNotes");
    QDomElement tasks = activeNotes.firstChildElement("tasks");
    QDomElement task = tasks.firstChildElement("task");

    std::vector<Task*> tab;

    for(;!task.isNull(); task = task.nextSiblingElement("task")) {
        Task *a = new Task(
            task.firstChildElement("id").text(),
            task.firstChildElement("title").text(),
            task.firstChildElement("createdOn").text(),
            task.firstChildElement("lastModifOn").text()
        );

        tab.push_back(a);
    }

    return tab;
}

XMLManager::~XMLManager() {
    doc.close();
}
