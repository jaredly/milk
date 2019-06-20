
module Belt_Result = {
  type t('a, 'b) = Ok('a) | Error('b);
}
open Belt_Result;

let one = () => true ? Ok(5) : Error("hi");

let hello = () => "good";
