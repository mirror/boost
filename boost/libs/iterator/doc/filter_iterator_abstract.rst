The filter iterator adaptor creates a view of an iterator range in
which some elements of the range are skipped over. A predicate
function object controls which elements are skipped. When the
predicate is applied to an element, if it returns ``true`` then the
element is retained and if it returns ``false`` then the element is
skipped over. When skipping over elements, it is necessary for the
filter adaptor to know when to stop so as to avoid going past the end
of the underlying range. Therefore the constructor of the filter
iterator takes two iterator parameters: the position for the filtered
iterator and the end of the range.
