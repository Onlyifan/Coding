#ifndef _QUERY_HH_
#define _QUERY_HH_


#include "query_result.hh"
#include "text_query.hh"
#include <memory>
#include <ostream>
#include <string>


class Query_base {
    friend class Query;

  protected:
    virtual ~Query_base( ) = default;

  private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual std::string rep( ) const = 0;
};


class Query {
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);

  public:
    Query(const std::string &);
    QueryResult eval(const TextQuery &tq) const { return _pBase->eval(tq); }
    std::string rep( ) const { return _pBase->rep( ); }

  private:
    Query(std::shared_ptr<Query_base> pBase)
        : _pBase(pBase) {}

  private:
    std::shared_ptr<Query_base> _pBase;
};
inline std::ostream &operator<<(std::ostream &os, const Query &q) {
    return os << q.rep( );
}


class WordQuery : public Query_base {
    friend class Query;

  private:
    WordQuery(const std::string &str)
        : _word(str) {}

  private:
    QueryResult eval(const TextQuery &tq) const { return tq.query(_word); }

    std::string rep( ) const { return _word; }

  private:
    std::string _word;
};
inline Query::Query(const std::string &str)
    : _pBase(new WordQuery(str)) {}


class NotQuery : public Query_base {
    friend Query operator~(const Query &);

  private:
    NotQuery(const Query &q)
        : _query(q) {}

    QueryResult eval(const TextQuery &) const;
    std::string rep( ) const { return "~(" + _query.rep( ) + ")"; }

  private:
    Query _query;
};
inline Query operator~(const Query &q) {
    return std::shared_ptr<Query_base>(new NotQuery(q));
}


class BinaryQuery : public Query_base {
  protected:
    BinaryQuery(const Query &lhs, std::string opSymbol, const Query &rhs)
        : _lhs(lhs)
        , _opSymbol(opSymbol)
        , _rhs(rhs) {}
    std::string rep( ) const {
        return "(" + _lhs.rep( ) + " " + _opSymbol + " " + _rhs.rep( ) + ")";
    }

  protected:
    Query _lhs;
    Query _rhs;
    std::string _opSymbol;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);

  private:
    AndQuery(const Query &lhs, const Query &rhs)
        : BinaryQuery(lhs, "&&", rhs) {}

    QueryResult eval(const TextQuery &) const;
};
inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}


class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &, const Query &);

  private:
    OrQuery(const Query &lhs, const Query &rhs)
        : BinaryQuery(lhs, "||", rhs) {}

    QueryResult eval(const TextQuery &) const;
};
inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}


#endif // _QUERY_HH_
