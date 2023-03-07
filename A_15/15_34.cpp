/*
(a): 
WordQuery("fiery") -> Query("fiery")
WordQuery("bird")  -> Query("bird")
BinaryQuery(Query("fiery"), Query("bird"), &) -> AndQuery(Query("fiery"), Query("bird")) -> Query(tmp)
BinaryQuery(Query(tmp), Query("wind"), |) -> OrQuery(Query(tmp), Query("wind")) -> Query(result)  = Query q
*/