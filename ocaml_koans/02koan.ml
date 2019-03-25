(* string meditations *)


(* words can be be combined as well. *)
let stringadd =
  "this " ^ "is " ^ "true" = _

(* but once put together, a word isn't simple to adjust. *)
(* format : String.sub string start length *)
let robin = 
  "true this is as well"

let stringsub =
  String.sub robin 0 4 = _

let stringsub1 =
  "this" = _ _ _ _

(* you can inquire about some characteristics of words and learn. deep down it is all about learning. *)
(* format : String.length string *)

(* for example, you can see how long a word is *)
let fox =
  "find the length"

let strlen =
  String.length fox = _

(* or you can see if a character exists in a word. *)
(* format : String.contains string char *)
let bunny =
  "this many"

let inthere =
  true = _ _ _

(* there is truth in the equality of two things that are the same. *)
let sloth =
  "equal"

let streq =
  sloth = _





  














let () = 
  print_string "Testing part 4 ... " ;
  try

    assert (stringadd);
    assert (stringsub);
    assert (stringsub1);
    assert (strlen);
    assert (inthere);
    assert (streq);
    assert ();    
    assert ();

        print_string "tests passed.\n"
  with
    Assert_failure (file, line, column) -> 
    let msg = "\n\n\nTest failed on line " ^ string_of_int line ^ 
                ", column " ^ string_of_int column ^ "\n\n\n\n"
    in print_string msg