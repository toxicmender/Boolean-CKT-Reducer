# Boolean-CKT-Reducer
Boolean-CKT-Reducer is a program written in C++ that uses the "Tabulation Method" to reduce a given boolean circuit.

<h2><b>Procedure of Quine-McCluskey Tabular Method</b></h2>

Follow these steps for simplifying Boolean functions using Quine-McClukey tabular method.

<b>Step 1</b> − Arrange the given min terms in an ascending order and make the groups based on the number of ones present in their binary representations. So, there will be at most ‘n+1’ groups if there are ‘n’ Boolean variables in a Boolean function or ‘n’ bits in the binary equivalent of min terms.

<b>Step 2</b> − Compare the min terms present in successive groups. If there is a change in only one-bit position, then take the pair of those two min terms. Place this symbol ‘_’ in the differed bit position and keep the remaining bits as it is.

<b>Step 3</b> − Repeat step2 with newly formed terms till we get all prime implicants.

<b>Step 4</b> − Formulate the prime implicant table. It consists of set of rows and columns. Prime implicants can be placed in row wise and min terms can be placed in column wise. Place ‘1’ in the cells corresponding to the min terms that are covered in each prime implicant.

<b>Step 5</b> − Find the essential prime implicants by observing each column. If the min term is covered only by one prime implicant, then it is essential prime implicant. Those essential prime implicants will be part of the simplified Boolean function.

<b>Step 6</b> − Reduce the prime implicant table by removing the row of each essential prime implicant and the columns corresponding to the min terms that are covered in that essential prime implicant. Repeat step 5 for Reduced prime implicant table. Stop this process when all min terms of given Boolean function are over.
