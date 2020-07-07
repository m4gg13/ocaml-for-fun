(* list meditations *)


(* sometimes things fit into a group. *)
(* lists are groups that can be adjusted. *)
let numls =
  [3; 1; 4]

let charls =
  ['p'; 'i'; 'e']

let yourls =
  _

(* tuples, however, are groups that do not adjust. *)
let strtup =
  ("blueberry", "pecan", "chocolate silk")

let floattup =
  (3.0, 0.14, 0.0015, 0.000092)

let yourtup =
  _

(* tuples can hold elements of all kinds together. *)

let mixtup =
  (3.14, "cherry", 'π')

let yourmixtup =
  _

(* there can even be groups of other groups. "group groups." just kidding. *)
(* there are tuple lists... *)
let tupls =
  [(3, "three"); (1, "one"); (4, "four")]

let yourtupls =
  _

(* ...and in the interest of balance, list tuples. *)
let lstup =
  (["this"; "type"], ["of"; "pie"], ["is"; "rather"], ["unusual"])

let yourlstup =
  _

(* since lists can be adjusted, there are ways to adjust lists. *)
let ingredient =
  "grahm cracker crust"

let recipe =
  ["condensed milk"; "pumpkin"; "whipped cream"]

let spices =
  ["nutmeg"; "cinnamon"; "ginger"]

(* adding one element to the front of a list is called concatenation. *)
let add2front =
  ingredient :: recipe

(* adding a list to the front of another list can be done through appending. *)
let addls2ls =
  spices @ recipe

(* it is possible to put structures with names into other structures as well. *)
let all2gether =
  (ingredient, recipe, spices)

(* notice that among all of this adjusting, the original structures are never /changed/. new structures are created, but never the old ones changed. *)

let yourelem =
  _

let yourlsA =
  _

let yourlsB =
  _

let addyourelem2yourlsA =
  _

let addyourlsA2yourlsB =
  _

let yourelemandyourlsAandyourlsB2gether =
  _




  














let () = 
  print_string "Testing part 4 ... " ;
  try

    assert (addyourelem2yourlsA = yourelem :: yourlsA);
    assert (addyourlsA2yourlsB = yourlsA @ yourlsB);   

        print_string "tests passed.\n"
  with
    Assert_failure (file, line, column) -> 
    let msg = "\n\n\nTest failed on line " ^ string_of_int line ^ 
                ", column " ^ string_of_int column ^ "\n\n\n\n"
    in print_string msg