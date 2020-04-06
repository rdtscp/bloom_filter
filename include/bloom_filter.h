#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <string>
#include <vector>

namespace ads {

class bloom_filter {

public:
  /* Construct a bloom filter with correct number of hashes for a false positive
   * rate. */
  bloom_filter(const int num_entries, const double false_positive_rate);

  /* Construct a bloom filter of set size, and some initialising entries. */
  bloom_filter(const int num_entries, const double false_positive_rate,
               const std::vector<std::string> &entries);

  /* Initialiser-List Constructor */
  bloom_filter(const int num_entries, const double false_positive_rate,
               const std::initializer_list<std::string> &entries);

  /* Copy Constructor */
  bloom_filter(const bloom_filter &copy);

  /* Assignment Operator */
  bloom_filter &operator=(const bloom_filter &rhs);

  /* Insert an Element. */
  auto insert(const std::string &entry) -> void;

  /* Returns if an Element Exists in the Tree */
  auto find(const std::string &entry) const -> bool;

  /* Clears all Elements of the Binary Tree */
  auto clear() -> void;

  /* Returns a String Representation of the Bloom Filter. */
  auto dump() const -> std::string;

private:
  int num_hashes;
  std::vector<bool> bits;

  auto validate_args(const int num_entries,
                     const double false_positive_rate) const -> void;
  auto get_num_bits(const int num_entries,
                   const double false_positive_rate) const -> int;
  auto get_num_hashes(const int num_entries, const int num_bits) const -> int;
};

} // namespace ads

#endif