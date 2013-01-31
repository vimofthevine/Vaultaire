# Vaultaire

Vaultaire is a graphical front-end to standard Linux command line utilities
(scanimage, find, grep, etc.) that simplifies scanning, tagging, organizing,
and retrieving of documents, letters, receipts, etc.

Built on the Qt framework, Vaultaire is a graphical user interface that allows
users to scan documents and tag them for easy future retrieval. Scanned documents
are organized into a simple folder scheme that can easily be browsed with any
file manager. Meta data, such as date, category (e.g., XY Bank Statements, ABC
Utility), document title, and general tags, can be supplied when importing (i.e.,
scanning) a document. Meta data is stored in plain text files along with the
scanned image files, allowing standard unix search utilities (i.e., find) to be
used for file retrieval. Optionally, optical-character-recognition can be
performed on each scanned file to allow the actual contents of the document to
be searched.

Image resolution and file sizes are easily configured by providing the actual
`scanimage`, `convert`, or OCR commands to be used by Vaultaire.

License: Apache License 2.0

## How to build it

Run `make` from the top-level directory to build Vaultaire. Alternatively,
in the `client` directory, run `qmake` followed by `make`.

To install Vaultaire into the standard Linux directories, run `make install`
from the top-level directory.

## How to use it

Vaultaire requires a little bit of setup before it is actually usable. As
root, launch `vaultaire` and open the edit-settings dialog. In particular,
the following configuration items must be set:

* Library root: root directory where all scanned documents will go
* Scanner device: name of your scanner device as determined by the output
  of `scanimage -L`

**Do not use vaultaire as root!** All scanned documents will be owned by root,
preventing normal users from viewing them.

From the File->New option, provide information for the document to be scanned,
and hit the "Scan" button. Once scanned and imported into the library, it can
be seen in the library browser, or found in a search of the library.

