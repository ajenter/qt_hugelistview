# qt_hugelistview
Example of a huge list implemented with a QTableView, to work around QListView bug (Even with batchSize=10, QListView calls sizeHint for ALL items, which leads to a huge startup freeze)

Tested with:
- Qt 6.0.0 and 5.15.2 
- MSVC 2019 x64


