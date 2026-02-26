#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  auto space_iters = find_all(source.begin(), source.end(), isspace);
  std::set<Token> tokens;
  std::transform(
    space_iters.begin(), space_iters.end() - 1, space_iters.begin() + 1,
    std::inserter(tokens, tokens.end()),
    [&source](auto begin, auto end) {
      return Token(source, begin, end);
    }
  );
  std::erase_if(tokens, [](const auto& token) {
    return token.content.empty();
  });
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  auto view = 
    source 
    | rv::filter([&dictionary](const auto& token) { 
      return !dictionary.contains(token.content); 
    })
    | rv::transform([&dictionary](const auto& token) {
      auto view = 
        dictionary 
        | rv::filter([&token](const auto& word) {
          return levenshtein(token.content, word) == 1;
        });
      std::set<std::string> suggestions(view.begin(), view.end());
      return Misspelling { token, suggestions };
    })
    | rv::filter([](const auto& misspelling){
      return !misspelling.suggestions.empty();
    });

  return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"