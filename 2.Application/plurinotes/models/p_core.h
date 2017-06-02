#ifndef P_CORE
#define P_CORE

#include "main.h"
#include "p_notes.h"

class PluriNotes {

    private:
        ActiveNotesManager* activeNotesManager;
        ArchivedNotesManager* archivedNotesManager;
        DeletedNotesManager* deletedNotesManager;

    public:
        PluriNotes();
        ~PluriNotes();

        ActiveNotesManager* getActiveNotesManage() const { return activeNotesManager; }
        ArchivedNotesManager* getArchivedNotesManager() const { return archivedNotesManager; }
        DeletedNotesManager* getDeletedNotesManage() const { return deletedNotesManager; }
};

#endif // P_CORE
