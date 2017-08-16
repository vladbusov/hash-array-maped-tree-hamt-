![hamt](http://i.imgur.com/LbtuEa0.png)

## Operation
---------------
A HAMT is an array mapped trie where the keys are first hashed in order to ensure an even distribution of keys and a constant key length.

In a typical implementation of HAMT's array mapped trie, each node contains a table with some fixed number N of slots with each slot containing either a nil pointer or a pointer to another node. N is commonly 32. As allocating space for N pointers for each node would be expensive, each node instead contains a bitmap which is N bits long where each bit indicates the presence of a non-nil pointer. This is followed by an array of pointers equal in length to the number of ones in the bitmap, (its Hamming weight).

## Advantages of HAMTs
-------------------------
The hash array mapped trie achieves almost hash table-like speed while using memory much more economically. Also, a hash table may have to be periodically resized, an expensive operation, whereas HAMTs grow dynamically. Generally, HAMT performance is improved by a larger root table with some multiple of N slots; some HAMT variants allow the root to grow lazily[1] with negligible impact on performance.

- [x] speed
- [x] economical

* Item 1
* Item 2
  * Item 2a
  * Item 2b
