# qt_hugelistview
Example of QListView behavoir

Reproducible with:
- Qt 6.0.0 and 5.15.2 
- MSVC 2019 x64

Even with batchSize=10, QListView calls sizeHint for ALL items, which leads to a huge startup freeze!
