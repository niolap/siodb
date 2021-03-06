# CHECKLIST: ADD NEW SYSTEM TABLE

1. Update "docs/user/system_tables.md" with new table and columns.

2. Update "docs/dev/designs/SystemDataModel.txt" with new table and columns.

3. Update "common/lib/siodb/iomgr/shared/dbengine/SystemObjectNames.h" -
   include new table name and columns.

4. Update "iomgr/lib/dbengine/Database_Init.cpp" - Database::m_allSystemTables
   and Database::m_systemDatabaseOnlySystemTables.

5. Create new registry record data structure in the `iomgr/lib/dbengine/reg`.

6. Add registry record data structure UUID to the
   "iomgr/lib/dbengine/reg"RegistryRecordUuidChecker.cpp"

7. Create new registry data structure in the `iomgr/lib/dbengine/reg`.

8. Create object class in the `iomgr/lib/dbengine`.

9. Add files created on the steps 5-7 to the `iomgr/lib/dbengine/Makefile`.

10. Add table variable to the class `Database` or class `SystemDatabase`.

11. Create table and its columns in the `Database::Database()`
    or `SystemDatabase::SystemDatabase()` for the new database.

12. Create table with loadSystemTable() in the `Database::Database()`
    or `SystemDatabase::SystemDatabase()` for the existing database.

13. Add member function `Database::recordXXX()`
    (in the `iomgr/lib/dbengine/Database_RecordObjects.cpp`)
    or `SystemDatabase::recordXXX()`
    (in the `iomgr/lib/dbengine/SystemDatabase_RecordObjects.cpp`).

14. Add member function `Database::readAllXXX()`
    (in the `iomgr/lib/dbengine/Database_ReadObjects.cpp`)
    or `SystemDatabase::readAllXXX()`
    (in the `iomgr/lib/dbengine/SystemDatabase_ReadObjects.cpp`).

15. Possibly add other physical record management member functions like `Database::deleteXXX()`,
    `Database::updateXXX()` (in the `iomgr/lib/dbengine/Database_RecordObjects.cpp`)
    or `SystemDatabase::deleteXXX()` (in the `iomgr/lib/dbengine/SystemDatabase_RecordObjects.cpp`).

16. Add SQL test for the new table in the `tests/sql_tests/query_sys_tables.sql`, include all
    table fields into a new select statement.
