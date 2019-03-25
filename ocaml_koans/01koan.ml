(* basic logic meditations *)

(* things in the universe have defining characteristics. according
   to the directions in the README file, access the OCaml REPL. In
   OCaml, each expression has a type. run each of the following and
   observe the output.
    # () ;;
    # 1 ;;
    # 1.0 ;;
    # [0; 1; 2] ;;
    # (0.1; 2.3; 3.4) ;;
*)


(* there is an essential truth to the universe that can be employed. *)
let t =
  true = _

let f = 
  not false = _

let noteq =
  false = _

(* such as the fact that things can be combined... *)
let add = 
  1 + 1 = _

(* ...and separated. *)
let sub =
  2 - 1 = _

(* or that you must be sensitive to how things are identified when interacting with them. *)
let floatadd = 
  1.0 +. 2.0 = _

let floatsub =
  3.0 -. 4.0 = _

(* even nothing has some truth to it. *)
let none =
  () = _






  














let () = 
  print_string "Testing part 4 ... " ;
  try

    assert (t);
    assert (f);
    assert (noteq);
    assert (add);
    assert (sub);
    assert (floatadd);
    assert (floatsub);
    assert (none);    

        print_string "tests passed.\n"
  with
    Assert_failure (file, line, column) -> 
    let msg = "\n\n\nTest failed on line " ^ string_of_int line ^ 
                ", column " ^ string_of_int column ^ "\n\n\n\n"
    in print_string msg