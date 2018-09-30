#include <set>
#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include "../include/bloom_filter.h"

using namespace ads;

bloom_filter::bloom_filter(int num_entries, double false_postitive_rate) {
  int num_bits  = bloom_filter::get_num_bits(num_entries, false_postitive_rate);
  num_hashes    = bloom_filter::get_num_hashes(num_entries, num_bits);

  bits.resize(num_bits, 0);
}

bloom_filter::bloom_filter(int num_entries, double false_postitive_rate, const std::vector<std::string>& entries) {
  int num_bits      = bloom_filter::get_num_bits(num_entries, false_postitive_rate);
  num_hashes  = bloom_filter::get_num_hashes(num_entries, num_bits);
  
  bits.resize(num_bits, 0);

  for (std::string entry: entries)
    insert(entry);
}

bloom_filter::bloom_filter(int num_entries, double false_postitive_rate, const std::initializer_list<std::string>& entries) {
  int num_bits      = bloom_filter::get_num_bits(num_entries, false_postitive_rate);
  num_hashes  = bloom_filter::get_num_hashes(num_entries, num_bits);
  
  bits.resize(num_bits, 0);

  for (std::string entry: entries)
    insert(entry);
}

void bloom_filter::insert(const std::string& entry) {
  for (int hash_number = 0; hash_number < num_hashes; hash_number++) {

    unsigned long bits_idx = std::hash<std::string>{}(entry + std::to_string(hash_number));

    if (bits_idx < 0)
      bits_idx *= -1;

    bits_idx = bits_idx % (bits.capacity() - 1);

    bits[bits_idx] = true;
  }
}

bool bloom_filter::find(const std::string& entry) {
  int output = true;
  for (int hash_number = 0; hash_number < num_hashes; hash_number++) {
    unsigned long bits_idx = std::hash<std::string>{}(entry + std::to_string(hash_number));

    if (bits_idx < 0)
      bits_idx *= -1;

    bits_idx = bits_idx % (bits.capacity() - 1);

    output = output && bits[bits_idx];
  }
  return output;
}

void bloom_filter::clear() {
  std::fill(bits.begin(), bits.end(), false);
}

std::string bloom_filter::dump() {
  std::string output = "";
  for(int i = 0; i < bits.size(); i++)
    (bits[i]) ? output += "1" : output += "0";
  return output;
}

/* (-num_entries * log_2(false_postitive_rate)) / ln2 */
int bloom_filter::get_num_bits(int num_entries, double false_positive_rate) {
  return std::ceil((-1 * num_entries * std::log2(false_positive_rate)) / std::log(2));
}

/* ( num_bits / num_entries ) * ln2 */
int bloom_filter::get_num_hashes(int num_entries, int num_bits) {
  return std::ceil((num_bits / (double)num_entries) * std::log(2));
}