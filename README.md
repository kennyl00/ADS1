# __Autocomplete with Ternary Search Tree__ #

This program is written in C. It first loads all the data entries from a `datafile.csv` and forms a [Ternary Search Tree](https://en.wikipedia.org/wiki/Ternary_search_tree). It then searches for the `prefix`, and displays all the matching entries to an `outputfile` and to the console. 
* `autocomplete1` does not sort the results
* `autocomplete2` sorts the results by using Selection Sort.




To run the program
```
make [autocomplete1 or autocomplete2]
./[autocomplete1 or autocomplete2] [datafile.csv] [outputfile] [prefix]
```

Note: Make sure the `datafile.csv` is at the same folder as the program
