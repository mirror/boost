
* use of "returns"
* [Metafunction Class] form ('f<>')
* nested 'algo' namespace??? it becomes a problem as soon as users would
    want to specialize 'advance'/'distance'
    
* 'outer' scope construct for lambda
* 'scope/fun/func'
* iterators not requiring nested members; what about '::type', though?
*  We don't dispatch _every_ metafunction through the tag mechanism, 
    only algorithms. I am ambivalent whether we should, and if so, 
    how it should be done. 
    
* 'drop_front'?