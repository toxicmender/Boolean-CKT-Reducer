# Boolean-CKT-Reducer

## About

Boolean-CKT-Reducer (Boolean Circuit Reducer) is a console application written in C++ that uses *"Quine-McCluskey's Tabular Method"* to reduce a given Boolean Expression.

## Quine-McCluskey Tabular Method

* **Step 1** − *Arrange the given [min terms](https://en.wikipedia.org/wiki/Canonical_normal_form#Minterms) in an ascending order and make the groups based on the number of ones present in their binary representations. So, there will be at most ‘n+1’ groups if there are ‘n’ Boolean variables in a Boolean function or ‘n’ bits in the binary equivalent of min terms.*

* **Step 2** − *Compare the min terms present in successive groups. If there is a change in only one-bit position, then take the pair of those two min terms. Place this symbol ‘_’ in the differed bit position and keep the remaining bits as it is.*

* **Step 3** − *Repeat step2 with newly formed terms till we get all [prime implicants](https://en.wikipedia.org/wiki/Implicant#Prime_implicant).*

* **Step 4** − *Formulate the prime implicant table. It consists of set of rows and columns. Prime implicants can be placed in row wise and min terms can be placed in column wise. Place ‘1’ in the cells corresponding to the min terms that are covered in each prime implicant.*

* **Step 5** − *Find the [essential prime implicants](https://en.wikipedia.org/wiki/Implicant#Prime_implicant) by observing each column. If the min term is covered only by one prime implicant, then it is essential prime implicant. Those essential prime implicants will be part of the simplified Boolean function.*

* **Step 6** − *Reduce the prime implicant table by removing the row of each essential prime implicant and the columns corresponding to the min terms that are covered in that essential prime implicant. Repeat step 5 for Reduced prime implicant table. Stop this process when all min terms of given Boolean function are over.*

## Current Status

*The program is in **Beta** version*

## Prerequisites and Deployement

*This program is a console application written in C++ and hence needs a C++ compiler to Compile and Run*

### 1. Downloading the source file

Lastest source file is available at 
```
https://github.com/shashank9830/Boolean-CKT-Reducer/src/boolean_ckt_reduce.cpp
```

### 2. Compiling and running the program

Recommended IDE

**Microsoft Visual Studio Community 2017**
```
https://www.visualstudio.com/downloads/
```

**CodeBlocks** 
```
http://codeblocks.org/
```

Users can use any other IDE that supports Compiling and Debugging of C++ source files.

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **Shashank Singh** - *Initial work* - [shashank9830](https://github.com/shashank9830)

See also the list of [contributors](https://github.com/shashank9830/Boolean-CKT-Reducer/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to [PurpleBooth](https://github.com/PurpleBooth) for the [README-Template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2).
* Cheers to all the [contributors](https://github.com/shashank9830/Boolean-CKT-Reducer/contributors) who contributed to the project.
