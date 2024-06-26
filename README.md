# Segment Tree Printer
A simple class that allows to visualize segment trees in the terminal.

## How to use it
#### In your file:
- Download the [source file](st_printer.cpp) (named [st_printer.cpp](st_printer.cpp)).
- Put it inside of your current work directory.
- Instantiate a **TreePrinter** object with the type of your node as its template parameter.
- Invoke the _print_ function of said object with the specified parameters:

#### At compile time:
- Include the file when compiling. For example, if you want to compile a file named "main.cpp", compile it with "g++ main.cpp [st_printer.cpp](st_printer.cpp)".
- **NOTE**: this step seems unnecesary, use it only if normal compilation isn't working.

#### To use your own node type:
- Create a **static** function that takes a single argument with the same type as the nodes of your segment tree and returns a string.