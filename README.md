# getBN-probability
We estimate a class variable conditional probability of Bayesian Network  (BN).

<!-- Badges -->
<table>
    <tr>
        <td>License</td>
        <td>Lang</td>
        <td>Editor</td>
    </tr>
    <tr>
        <td>
            <img src="http://img.shields.io/badge/license-MIT-blue.svg?style=flat">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-C++-00599C.svg?logo=cplusplus">
            <img src="https://img.shields.io/badge/-Boost-00599C.svg?logo=boost">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-VSCode-007ACC.svg?logo=visualstudiocode">
        </td>
    </tr>
</table>

# Overview
A Bayesian network (BN) is a graphical model that represents conditional independence among random variables as a directed acyclic graph (DAG).  

Let $\{x_0, x_1, x_2, \dotsc, x_n\}$ be a set of $n + 1$ discrete variables.
Each can take values in the set of states $\{1, \dotsc, r_i\}$.

We estimate the probability distribution of the class variable given the feature variables $p(x_0 \mid x_1, x_2, \dotsc, x_n ) \ (x_0: \text{class variable}, x_1, x_2, \dotsc, x_n: \text{feature variable})$ of BN $(G, \Theta) \ (G: \text{DAG}, \Theta: \text{a set of conditional probabilistic parametes})$.  

We calculate this as below:  

$$
\begin{align}
    p(x_0 \mid x_1, x_2, \dotsc, x_n, G, \Theta) &= \frac{p(x_0 , x_1, x_2, \dotsc, x_n \mid G, \Theta)}{p( x_1, x_2, \dotsc, x_n \mid G, \Theta)}\nonumber\\
    &= \frac{p(x_0 , x_1, x_2, \dotsc, x_n \mid G, \Theta)}{\sum_{k = 1}^{r_0}{p(x_0 = k, x_1, x_2, \dotsc, x_n \mid G, \Theta)}} 
\end{align}
$$



# Install 
This project requires [Boost](http://www.boost.org/). Please see the documentation for more details.

# Usage
This package entails following steps:
## 1. build
```
mkdir build  
cmake -S . -B build
cd build
make
```


## 2. estimate the probabilistic distribution
```
cd ..
cd build/bin/
./main <adjacency matrix(csv format)>  <data(csv format) path> <output path> -t <target variable>
```
The ```-help```command line option will show more information about main program. For example:
```
./main --help
```
# Example
```
% ./main ../../test/cancer_struct.csv ../../test/cancer_10000.csv -v 2 -t 2 

validation: 0

state[0]: 0.214890, state[1]: 0.785110
state[0]: 0.199726, state[1]: 0.800274
state[0]: 0.214890, state[1]: 0.785110
state[0]: 0.200504, state[1]: 0.799496
*
*
*
state[0]: 0.241144, state[1]: 0.758856
state[0]: 0.241144, state[1]: 0.758856
state[0]: 0.189577, state[1]: 0.810423
0.420000s wall, 0.390000s user + 0.000000s system = 0.390000s CPU (92.9%)
```

# License
The source code is licensed MIT.


