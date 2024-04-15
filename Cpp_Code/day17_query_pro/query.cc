#include "query.hh"
#include "query_result.hh"


using std::set;
using std::shared_ptr;

QueryResult NotQuery::eval(const TextQuery &tq) const {
    QueryResult                  result = _query.eval(tq);
    shared_ptr<set<std::size_t>> pSet(new set<size_t>);

    for (size_t i = 0; i != result.size( ); ++i) {
        pSet->insert(i);
    }
    for (auto it = result.begin( ); it != result.end( ); ++it) {
        pSet->erase(*it);
    }

    return QueryResult(rep( ), pSet, result.getFile( ));
}


QueryResult AndQuery::eval(const TextQuery &tq) const {
    QueryResult lResult = _lhs.eval(tq);
    QueryResult rResult = _rhs.eval(tq);

    shared_ptr<set<std::size_t>> pSet(new set<size_t>);
    for (auto it = lResult.begin( ); it != lResult.end( ); ++it) {
        if (std::find(rResult.begin( ), rResult.end( ), *it) != rResult.end( )) {
            pSet->insert(*it);
        }
    }


    return QueryResult(rep( ), pSet, lResult.getFile( ));
}
QueryResult OrQuery::eval(const TextQuery &tq) const {
    QueryResult lResult = _lhs.eval(tq);
    QueryResult rResult = _rhs.eval(tq);

    shared_ptr<set<std::size_t>> pSet(new set<size_t>);
    pSet->insert(lResult.begin( ), lResult.end( ));
    pSet->insert(rResult.begin( ), rResult.end( ));


    return QueryResult(rep( ), pSet, lResult.getFile( ));
}
