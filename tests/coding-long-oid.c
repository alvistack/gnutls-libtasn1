/*
 * Copyright (C) 2016 Free Software Foundation, Inc.
 *
 * This file is part of LIBTASN1.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libtasn1.h>

/* This checks the decoding and re-encoding of OIDs which contain elements
 * >= 2^32 bits.
 */

const unsigned char der_data[] =
	"\x30\x82\x06\xdc\x30\x82\x05\xc4\xa0\x03\x02\x01\x02\x02\x08\x35"
	"\x73\x8c\xaf\x21\xea\xbd\x2d\x30\x0d\x06\x09\x2a\x86\x48\x86\xf7"
	"\x0d\x01\x01\x05\x05\x00\x30\x81\x8e\x31\x0b\x30\x09\x06\x03\x55"
	"\x04\x06\x13\x02\x55\x53\x31\x17\x30\x15\x06\x03\x55\x04\x08\x13"
	"\x0e\x4e\x6f\x72\x74\x68\x20\x43\x61\x72\x6f\x6c\x69\x6e\x61\x31"
	"\x10\x30\x0e\x06\x03\x55\x04\x07\x13\x07\x52\x61\x6c\x65\x69\x67"
	"\x68\x31\x10\x30\x0e\x06\x03\x55\x04\x0a\x13\x07\x4b\x61\x74\x65"
	"\x6c\x6c\x6f\x31\x14\x30\x12\x06\x03\x55\x04\x0b\x13\x0b\x53\x6f"
	"\x6d\x65\x4f\x72\x67\x55\x6e\x69\x74\x31\x2c\x30\x2a\x06\x03\x55"
	"\x04\x03\x13\x23\x73\x61\x74\x2d\x72\x32\x32\x30\x2d\x31\x30\x2e"
	"\x6c\x61\x62\x2e\x65\x6e\x67\x2e\x72\x64\x75\x32\x2e\x72\x65\x64"
	"\x68\x61\x74\x2e\x63\x6f\x6d\x30\x1e\x17\x0d\x31\x36\x30\x37\x30"
	"\x31\x31\x38\x35\x34\x31\x37\x5a\x17\x0d\x34\x39\x31\x32\x30\x31"
	"\x31\x33\x30\x30\x30\x30\x5a\x30\x2b\x31\x29\x30\x27\x06\x03\x55"
	"\x04\x03\x13\x20\x38\x61\x38\x38\x38\x30\x31\x37\x35\x35\x61\x37"
	"\x63\x39\x30\x37\x30\x31\x35\x35\x61\x37\x63\x66\x62\x65\x33\x36"
	"\x30\x30\x30\x34\x30\x82\x01\x22\x30\x0d\x06\x09\x2a\x86\x48\x86"
	"\xf7\x0d\x01\x01\x01\x05\x00\x03\x82\x01\x0f\x00\x30\x82\x01\x0a"
	"\x02\x82\x01\x01\x00\xdc\x70\x8b\x9c\x84\xe9\x3e\x79\x8f\x03\xe5"
	"\x5f\x21\xf0\x29\x9e\xd9\x94\x4e\x0f\x37\x45\x47\x42\xda\x2a\xe0"
	"\xda\xf5\x8b\xfa\xe1\xf8\x62\x51\x14\x9d\x9e\xe0\xc7\x69\xd0\x3d"
	"\xfc\x25\x2f\xb6\x10\x45\xbd\x0d\xbc\x92\x86\x54\xbb\x4e\x7d\xd4"
	"\x92\x75\x65\xba\x48\xa4\x64\xa1\xeb\xf7\xe7\xdc\xc0\xd7\x0a\x5e"
	"\x36\x13\x0e\x4e\x35\xcc\x2c\xc6\xf3\xe7\xe7\xe5\x32\x8a\x0c\xf7"
	"\x47\x28\x7a\x02\xc2\x68\x66\x19\x3a\xba\xca\x31\xe2\xdd\x43\xbe"
	"\x26\x4c\x80\x12\x0c\xae\x44\x40\xeb\x69\x7d\x9e\x58\xd3\xab\xaf"
	"\x69\xe6\x54\xae\x7d\x80\xee\x2c\x10\xe9\xbb\x5e\x6b\x89\x15\x2e"
	"\x2c\x72\x26\xba\x7f\xe5\xa3\x66\xc5\x98\xc6\x57\xbf\x05\x1e\x55"
	"\x93\xa6\x16\x83\xa6\x88\x79\x8f\x4e\xb5\x7e\x70\xeb\xf0\xa9\xa6"
	"\xd5\xf9\x1f\xe6\xab\x70\x06\x43\xe0\xde\x82\xad\x0e\x04\x17\x2b"
	"\x69\x82\x40\x98\x84\x14\x00\x2a\xa2\xda\x61\x7b\x35\xac\x71\x05"
	"\x43\x6f\x55\x3a\x28\x4b\xd1\xa4\xeb\x3b\xf5\x03\xc2\xf8\x3c\xfd"
	"\x0a\xc4\x99\x1d\xa7\x7d\x08\x5c\xd1\x15\x70\x73\xb9\xdc\x5c\xf2"
	"\xfe\x2c\xc6\x21\x8a\xbe\xbd\x52\x37\x64\x04\xe5\x06\x3e\xc6\x62"
	"\xa1\xe9\x8e\xcb\xc1\x02\x03\x01\x00\x01\xa3\x82\x03\x9e\x30\x82"
	"\x03\x9a\x30\x11\x06\x09\x60\x86\x48\x01\x86\xf8\x42\x01\x01\x04"
	"\x04\x03\x02\x05\xa0\x30\x0b\x06\x03\x55\x1d\x0f\x04\x04\x03\x02"
	"\x04\xb0\x30\x81\xc3\x06\x03\x55\x1d\x23\x04\x81\xbb\x30\x81\xb8"
	"\x80\x14\xca\xca\x62\x86\x04\x05\xf0\xf5\x9b\x38\xd2\x2c\x3c\x8c"
	"\x65\x0f\xc6\xba\xa5\x3c\xa1\x81\x94\xa4\x81\x91\x30\x81\x8e\x31"
	"\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x55\x53\x31\x17\x30\x15"
	"\x06\x03\x55\x04\x08\x13\x0e\x4e\x6f\x72\x74\x68\x20\x43\x61\x72"
	"\x6f\x6c\x69\x6e\x61\x31\x10\x30\x0e\x06\x03\x55\x04\x07\x13\x07"
	"\x52\x61\x6c\x65\x69\x67\x68\x31\x10\x30\x0e\x06\x03\x55\x04\x0a"
	"\x13\x07\x4b\x61\x74\x65\x6c\x6c\x6f\x31\x14\x30\x12\x06\x03\x55"
	"\x04\x0b\x13\x0b\x53\x6f\x6d\x65\x4f\x72\x67\x55\x6e\x69\x74\x31"
	"\x2c\x30\x2a\x06\x03\x55\x04\x03\x13\x23\x73\x61\x74\x2d\x72\x32"
	"\x32\x30\x2d\x31\x30\x2e\x6c\x61\x62\x2e\x65\x6e\x67\x2e\x72\x64"
	"\x75\x32\x2e\x72\x65\x64\x68\x61\x74\x2e\x63\x6f\x6d\x82\x09\x00"
	"\xa4\xe7\xca\xeb\xbe\x43\x5d\xcc\x30\x1d\x06\x03\x55\x1d\x0e\x04"
	"\x16\x04\x14\x0e\x8d\x7b\x53\xba\x5a\x9e\x92\x44\xe5\x64\x58\xa1"
	"\xdb\x83\x47\x05\x3e\x32\xd3\x30\x13\x06\x03\x55\x1d\x25\x04\x0c"
	"\x30\x0a\x06\x08\x2b\x06\x01\x05\x05\x07\x03\x02\x30\x2a\x06\x10"
	"\x2b\x06\x01\x04\x01\x92\x08\x09\x01\xaa\xda\xbe\xbe\xfa\x5b\x01"
	"\x04\x16\x0c\x14\x6d\x6f\x72\x64\x6f\x72\x5f\x75\x65\x62\x65\x72"
	"\x5f\x70\x72\x6f\x64\x75\x63\x74\x30\x16\x06\x10\x2b\x06\x01\x04"
	"\x01\x92\x08\x09\x01\xaa\xda\xbe\xbe\xfa\x5b\x03\x04\x02\x0c\x00"
	"\x30\x16\x06\x10\x2b\x06\x01\x04\x01\x92\x08\x09\x01\xaa\xda\xbe"
	"\xbe\xfa\x5b\x02\x04\x02\x0c\x00\x30\x16\x06\x10\x2b\x06\x01\x04"
	"\x01\x92\x08\x09\x01\xaa\xda\xbe\xbe\xfa\x5b\x05\x04\x02\x0c\x00"
	"\x30\x19\x06\x10\x2b\x06\x01\x04\x01\x92\x08\x09\x02\xaa\xda\xbe"
	"\xbe\xfa\x72\x01\x04\x05\x0c\x03\x79\x75\x6d\x30\x24\x06\x11\x2b"
	"\x06\x01\x04\x01\x92\x08\x09\x02\xaa\xda\xbe\xbe\xfa\x72\x01\x01"
	"\x04\x0f\x0c\x0d\x75\x65\x62\x65\x72\x5f\x63\x6f\x6e\x74\x65\x6e"
	"\x74\x30\x32\x06\x11\x2b\x06\x01\x04\x01\x92\x08\x09\x02\xaa\xda"
	"\xbe\xbe\xfa\x72\x01\x02\x04\x1d\x0c\x1b\x31\x34\x36\x37\x33\x39"
	"\x39\x32\x35\x37\x34\x33\x35\x5f\x75\x65\x62\x65\x72\x5f\x63\x6f"
	"\x6e\x74\x65\x6e\x74\x30\x1d\x06\x11\x2b\x06\x01\x04\x01\x92\x08"
	"\x09\x02\xaa\xda\xbe\xbe\xfa\x72\x01\x05\x04\x08\x0c\x06\x43\x75"
	"\x73\x74\x6f\x6d\x30\x1e\x06\x11\x2b\x06\x01\x04\x01\x92\x08\x09"
	"\x02\xaa\xda\xbe\xbe\xfa\x72\x01\x06\x04\x09\x0c\x07\x2f\x6d\x6f"
	"\x72\x64\x6f\x72\x30\x17\x06\x11\x2b\x06\x01\x04\x01\x92\x08\x09"
	"\x02\xaa\xda\xbe\xbe\xfa\x72\x01\x07\x04\x02\x0c\x00\x30\x18\x06"
	"\x11\x2b\x06\x01\x04\x01\x92\x08\x09\x02\xaa\xda\xbe\xbe\xfa\x72"
	"\x01\x08\x04\x03\x0c\x01\x31\x30\x24\x06\x0a\x2b\x06\x01\x04\x01"
	"\x92\x08\x09\x04\x01\x04\x16\x0c\x14\x6d\x6f\x72\x64\x6f\x72\x5f"
	"\x75\x65\x62\x65\x72\x5f\x70\x72\x6f\x64\x75\x63\x74\x30\x10\x06"
	"\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04\x02\x04\x02\x0c\x00\x30"
	"\x1d\x06\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04\x03\x04\x0f\x0c"
	"\x0d\x31\x34\x36\x37\x33\x39\x39\x32\x35\x37\x34\x33\x35\x30\x11"
	"\x06\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04\x05\x04\x03\x0c\x01"
	"\x31\x30\x24\x06\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04\x06\x04"
	"\x16\x0c\x14\x32\x30\x31\x36\x2d\x30\x37\x2d\x30\x31\x54\x31\x38"
	"\x3a\x35\x34\x3a\x31\x37\x5a\x30\x24\x06\x0a\x2b\x06\x01\x04\x01"
	"\x92\x08\x09\x04\x07\x04\x16\x0c\x14\x32\x30\x34\x39\x2d\x31\x32"
	"\x2d\x30\x31\x54\x31\x33\x3a\x30\x30\x3a\x30\x30\x5a\x30\x11\x06"
	"\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04\x0c\x04\x03\x0c\x01\x30"
	"\x30\x11\x06\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04\x0e\x04\x03"
	"\x0c\x01\x30\x30\x11\x06\x0a\x2b\x06\x01\x04\x01\x92\x08\x09\x04"
	"\x0b\x04\x03\x0c\x01\x31\x30\x34\x06\x0a\x2b\x06\x01\x04\x01\x92"
	"\x08\x09\x05\x01\x04\x26\x0c\x24\x39\x34\x35\x33\x66\x38\x65\x36"
	"\x2d\x38\x34\x62\x32\x2d\x34\x38\x32\x65\x2d\x61\x33\x65\x61\x2d"
	"\x30\x31\x63\x33\x62\x33\x65\x32\x36\x36\x61\x35\x30\x0d\x06\x09"
	"\x2a\x86\x48\x86\xf7\x0d\x01\x01\x05\x05\x00\x03\x82\x01\x01\x00"
	"\xf7\x4d\xf3\x30\x53\xcd\x35\xbf\x49\x07\x29\x9b\xf0\x7a\xaa\x49"
	"\x60\xda\xce\x14\x45\xb5\x32\x8f\xda\xc3\xce\x6b\xec\xbf\x20\xc0"
	"\x05\xa3\x3a\x89\xc4\x7d\x66\x34\xfc\xf3\x16\xb8\xf3\x03\xda\xfc"
	"\x82\x4a\xb8\x97\xf8\x67\x3d\xc2\x8c\x78\xb4\x6d\xb8\xbb\x18\xec"
	"\x36\xee\xc4\x28\x79\xda\xfe\xa1\x1f\xaf\x0b\x3f\xe4\x75\xde\x83"
	"\xff\x6b\xf9\x11\x60\x09\x57\xea\x85\x34\xed\x60\xe2\x94\x8b\xd6"
	"\xf2\x21\x9b\xda\x97\x99\xf3\x0d\xa9\x0f\xb5\x3b\x3a\x8f\x96\x8d"
	"\x0b\xdf\x30\x17\x03\xe6\x47\xc3\x71\x32\x09\x18\xbc\xc0\xa9\x83"
	"\x7e\xb7\x5f\x5c\xbb\xeb\x0a\x18\x3f\xa9\x40\x98\xae\x57\xab\x99"
	"\x3d\x47\x1b\x98\x8a\xdc\x6e\x85\xa2\xea\x5e\x21\x80\xa9\xb5\x48"
	"\xc9\x1d\x63\xc1\x1b\xe6\x01\xa1\xbd\x84\x38\x7f\x1a\x43\xa5\xd4"
	"\x7f\x41\x5b\xf6\x88\x33\xb0\xf1\xb8\x8f\xe1\x39\x69\x6f\x60\x13"
	"\xd3\x5d\x70\xde\x95\x0d\x2f\xa9\x89\x6c\xd4\x3a\xeb\x22\x59\xe6"
	"\x31\x67\x71\xa5\xed\xfb\xcb\x20\x11\x0c\x31\x2e\xe0\x98\x9a\x3b"
	"\x9c\x7b\xa2\x74\x6f\x87\x97\xa1\xd9\x82\x7f\x7d\x62\x6b\x45\x6c"
	"\x0b\x5e\x25\x43\x8a\x20\x16\x7d\xe5\x84\x18\x3f\x7c\xda\xfc\xf9";

int der_data_size = sizeof(der_data)-1;

char new_data[4*1024];

int
main (int argc, char** argv)
{
  int result = 0;
  asn1_node definitions = NULL, node1 = NULL;
  char errorDescription[ASN1_MAX_ERROR_DESCRIPTION_SIZE];
  const char *pkixfile = getenv ("ASN1PKIX");
  int new_data_size;

  if (!pkixfile)
    pkixfile = "pkix.asn";

  /* Encode */
  result = asn1_parser2tree (pkixfile, &definitions, errorDescription);
  if (result != ASN1_SUCCESS)
    {
      printf ("error in %d: %s\n", __LINE__, errorDescription);
      exit (1);
    }

  result = asn1_create_element (definitions, "PKIX1.Certificate", &node1);
  if (result != ASN1_SUCCESS)
    {
      printf ("error in %d\n", __LINE__);
      exit (1);
    }

  result = asn1_der_decoding (&node1, der_data, der_data_size, errorDescription);
  if (result != ASN1_SUCCESS)
    {
      printf ("error in %d: %s\n", __LINE__, errorDescription);
      exit (1);
    }

  new_data_size = sizeof(new_data);
  result = asn1_der_coding (node1, "", new_data, &new_data_size, errorDescription);
  if (result != ASN1_SUCCESS)
    {
      printf ("error in %d\n", __LINE__);
      exit (1);
    }

  if (new_data_size != der_data_size)
    {
      printf ("error in %d\n", __LINE__);
      printf ("new_size is %d, expected: %d\n", new_data_size, der_data_size);
      exit (1);
    }

  if (memcmp(new_data, der_data, der_data_size) != 0)
    {
      printf ("error in %d\n", __LINE__);
      exit (1);
    }

  asn1_delete_structure (&node1);
  asn1_delete_structure (&definitions);

  return 0;
}
