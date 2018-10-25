#include <eosiolib/eosio.hpp>
#include <chrono>
#include <tuple>
#include <vector>

extern "C" {
    bool assert_recover_key(digest, sig, siglen, pub, publen);
};

using namespace eosio;

class bidirectional : public eosio::contract {

public:
  using contract::contract;

  bidirectional(account_name self, vector<account_name> accounts, std::chronon::seconds sec_til_close): contract(self) {

  }

private:
  // note: only 1 row. any better way?
  struct [[eosio::table]] meta {
    std::chronon::seconds sec_til_close;
    uint64_t primary_key() const { return 1; }
  }
  typedef eosio::multi_index<N(metas), meta> meta_index;

  struct [[eosio::table]] user {
    account_name user_name;
    uint64_t primary_key() const { return user_name; }
  };
  typedef eosio::multi_index<N(users), user> users_index;

  struct [[eosio::table]] transfer {
    uint64_t nonce;
    account_name from;
    account_name to;
    asset quantity;
    std::string memo;
    std::string sig;
    std::tuple<account_name, uint64_t> primary_key() const { return std::make_tuple(from, nonce); }
  };
  typedef eosio::multi_index<N(transfers), transfer> transfers_index;
};
