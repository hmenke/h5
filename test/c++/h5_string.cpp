
#include "./test_common.hpp"

#include <h5/h5.hpp>
#include <string>

TEST(H5, Encoding) {

  std::string ascii_str = "Hello World!";
  std::string utf8_str  = "Price: 10 €";

  {
    h5::file file("test_string.h5", 'w');

    // Store ASCII (internally uses UTF8 encoding)
    h5_write(file, "ASCII", ascii_str);
    h5_write_attribute(file, "ASCII_Attr", ascii_str);

    // Store UTF8
    h5_write(file, "UTF8", utf8_str);
    h5_write_attribute(file, "UTF8_Attr", utf8_str);
  }

  {
    h5::file file("ascii.ref.h5", 'r');
    // Read ASCII stored with H5T_CSET_ASCII
    std::string ascii_str_read = "";
    h5_read(file, "ASCII", ascii_str_read);
    EXPECT_EQ(ascii_str, ascii_str_read);
    h5_read_attribute(file, "ASCII_Attr", ascii_str_read);
    EXPECT_EQ(ascii_str, ascii_str_read);
  }

  {
    h5::file file("test_string.h5", 'r');

    // Read ASCII stored with UTF8 encoding
    std::string ascii_str_read = "";
    h5_read(file, "ASCII", ascii_str_read);
    EXPECT_EQ(ascii_str, ascii_str_read);
    h5_read_attribute(file, "ASCII_Attr", ascii_str_read);
    EXPECT_EQ(ascii_str, ascii_str_read);

    // Read UTF8
    std::string utf8_str_read = "";
    h5_read(file, "UTF8", utf8_str_read);
    EXPECT_EQ(utf8_str, utf8_str_read);
    h5_read_attribute(file, "UTF8_Attr", utf8_str_read);
    EXPECT_EQ(utf8_str, utf8_str_read);
  }
}