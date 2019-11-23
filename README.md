#Ocaml Koans


(some sort of note about asserts is necessary here)

(also make this more concise!!)

Ocaml Koans are an easy way to get familiar with the functionality of the functional language Ocaml. You may even find that you learn some more broadly reaching lessons along the way!


These Koans were inspired by Clojure Koans, found at https://github.com/functional-koans/clojure-koans and written by user trptcolin. 


A comprehensive table of contents can be found in CONTENTS.txt.


To begin,


1. Install Opam 
  - Opam is an Ocaml package manager. It will make installation of Ocaml a breeze.
2. Install Ocaml
  - Run 
```
     $ opam install ocaml
```
  - In response to this, your shell should guide you through the installation of Ocaml.
  - For troubleshooting, refer to https://opam.ocaml.org/
3. Access the Ocaml REPL
  - Run
```
     $ ocaml
```
  - The REPL is an interactive environment in which you can use Ocaml in real time.
    ☆ You may try it out by running something like
```
       # 41 + 1 ;;
```
4. Open and edit the first Koan file, Koan01
  - Attempt to answer the questions correctly. 
  - Feel free to browse resources such as Ocaml documentation, found at https://caml.inria.fr/pub/docs/manual-ocaml/libref/
    ☆ The most useful pages from this website are the following:
    ☆ https://caml.inria.fr/pub/docs/manual-ocaml/libref/List.html
    ☆ https://caml.inria.fr/pub/docs/manual-ocaml/libref/Pervasives.html
    ☆ https://caml.inria.fr/pub/docs/manual-ocaml/libref/String.html
5. Test your answers for Koan01
  - Way 2
    ☆ On the command line, run
```
      $ ocaml Koan01.ml
```
  - Way 1
    ☆ In the OCaml REPL, run
```
       # #use "Koan01.ml" ;;
```
    ☆ Observe the feedback messages and proceed accordingly.
6. Be persistent; do not give up along The Way.