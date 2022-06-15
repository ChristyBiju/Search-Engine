# Search Engine (DSA-II Project)
Search Engine implemented using Splay Trees and Trie Data Structure in C <br /> <br />
Christy Biju <br />
MIS : 112003031 <br />
Computer Engineering (Division 1)

## Functions which can be performed :
* -s : Searching questions
* -a [Prefix] : Autosuggestions from the entered prefix
* -r : Recently searched question
* -h : Displays History
* -fm : Most frequently searched questions
* -fl : Least Searched questions
* -d : Clearing the brower history 

## Data Structures used :
* **Trie**:Trie is a sorted tree-based data-structure that stores the set of strings.<br /> Used for implementing the search function and the autocomplete function.<br />The end of the question is represented with 1 and at the last character node the answer array is stored.<br />Time Complexity for searching the question and retrieving the answer would be O(L) ; L is length of the question<br /> 
* **Splay Trees**:Used for accessing the recently searched question and most frequently searched questions as the time complexity for these functions would be O(1).<br />Also used for displaying history with respective date

