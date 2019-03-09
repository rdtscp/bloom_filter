#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/bloom_filter.h"

using namespace ads;

bloom_filter::bloom_filter(const int num_entries,
                           const double false_positive_rate) {
  validate_args(num_entries, false_positive_rate);
  const int num_bits =
      bloom_filter::get_num_bits(num_entries, false_positive_rate);
  num_hashes = bloom_filter::get_num_hashes(num_entries, num_bits);

  bits.resize(num_bits, 0);
}

bloom_filter::bloom_filter(const int num_entries,
                           const double false_positive_rate,
                           const std::vector<std::string> &entries) {
  validate_args(num_entries, false_positive_rate);
  const int num_bits =
      bloom_filter::get_num_bits(num_entries, false_positive_rate);
  num_hashes = bloom_filter::get_num_hashes(num_entries, num_bits);

  bits.resize(num_bits, 0);

  for (std::string entry : entries)
    insert(entry);
}

bloom_filter::bloom_filter(const int num_entries,
                           const double false_positive_rate,
                           const std::initializer_list<std::string> &entries) {
  validate_args(num_entries, false_positive_rate);
  const int num_bits =
      bloom_filter::get_num_bits(num_entries, false_positive_rate);
  num_hashes = bloom_filter::get_num_hashes(num_entries, num_bits);

  bits.resize(num_bits, 0);

  for (std::string entry : entries)
    insert(entry);
}

bloom_filter::bloom_filter(const bloom_filter &copy)
    : num_hashes(copy.num_hashes), bits(copy.bits) {
  num_hashes = copy.num_hashes;
  bits = copy.bits;
}

bloom_filter &bloom_filter::operator=(const bloom_filter &rhs) {
  if (&rhs == this) {
    return *this;
  }

  num_hashes = rhs.num_hashes;
  bits = rhs.bits;
  return *this;
}

void bloom_filter::insert(const std::string &entry) {
  for (int hash_number = 0; hash_number < num_hashes; hash_number++) {

    unsigned long bits_idx = (unsigned long)std::hash<std::string>{}(
        entry + std::to_string(hash_number));

    bits_idx = bits_idx % (bits.capacity() - 1);

    bits[bits_idx] = true;
  }
}

bool bloom_filter::find(const std::string &entry) const {
  int output = true;
  for (int hash_number = 0; hash_number < num_hashes; hash_number++) {
    unsigned long bits_idx = (unsigned long)std::hash<std::string>{}(
        entry + std::to_string(hash_number));

    bits_idx = bits_idx % (bits.capacity() - 1);

    output = output && bits[bits_idx];
  }
  return output;
}

void bloom_filter::clear() { std::fill(bits.begin(), bits.end(), false); }

std::string bloom_filter::dump() const {
  std::string output = "";
  for (int i = 0; i < bits.size(); i++)
    (bits[i]) ? output += "1" : output += "0";
  return output;
}

void bloom_filter::validate_args(const int num_entries,
                                 const double false_positive_rate) const {
  if (false_positive_rate <= 0 || false_positive_rate >= 1)
    throw std::invalid_argument("bloom_filter must have a false_posive rate "
                                "between 0 and 1 exclusive.");
  if (num_entries <= 0)
    throw std::invalid_argument(
        "bloom_filter must have take a positive number of entries");
}

/* (-num_entries * log_2(false_positive_rate)) / ln2 */
int bloom_filter::get_num_bits(const int num_entries,
                               const double false_positive_rate) const {
  return std::ceil((-1 * num_entries * std::log2(false_positive_rate)) /
                   std::log(2));
}

/* ( num_bits / num_entries ) * ln2 */
int bloom_filter::get_num_hashes(const int num_entries,
                                 const int num_bits) const {
  return std::ceil((num_bits / (double)num_entries) * std::log(2));
}