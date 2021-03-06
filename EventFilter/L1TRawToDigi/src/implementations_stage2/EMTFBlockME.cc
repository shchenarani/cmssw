// Code to unpack the "ME Data Record"

#include "EventFilter/L1TRawToDigi/interface/Unpacker.h"
#include "EMTFCollections.h"
#include "EMTFUnpackerTools.h"

// This is the "header" - no EMTFBlockME.h file is needed
namespace l1t {
  namespace stage2 {
    namespace emtf {
      
      class MEBlockUnpacker : public Unpacker { // "MEBlockUnpacker" inherits from "Unpacker"
      public:
	// virtual bool checkFormat() override; // Return "false" if block format does not match expected format
	virtual bool unpack(const Block& block, UnpackerCollections *coll) override; // Apparently it's always good to use override in C++
	// virtual bool packBlock(const Block& block, UnpackerCollections *coll) override;
      };
      
      // class MEBlockPacker : public Packer { // "MEBlockPacker" inherits from "Packer"
      // public:
      // 	virtual bool unpack(const Block& block, UnpackerCollections *coll) override; // Apparently it's always good to use override in C++
      // };
      
    }
  }
}

namespace l1t {
  namespace stage2 {
    namespace emtf {

      bool MEBlockUnpacker::unpack(const Block& block, UnpackerCollections *coll) {
	
	// Get the payload for this block, made up of 16-bit words (0xffff)
	// Format defined in MTF7Payload::getBlock() in src/Block.cc
	// payload[0] = bits 0-15, payload[1] = 16-31, payload[3] = 32-47, etc.
	auto payload = block.payload();

	// Assign payload to 16-bit words
        uint16_t MEa = payload[0];
        uint16_t MEb = payload[1];
        uint16_t MEc = payload[2];
        uint16_t MEd = payload[3];

	// std::cout << "This payload has " << payload.size() << " 16-bit words" << std::endl;
	// for (uint iWord = 0; iWord < payload.size(); iWord++)
	//   std::cout << std::hex << std::setw(8) << std::setfill('0') << payload[iWord] << std::dec << std::endl;

	// res is a pointer to a collection of EMTFOutput class objects
	// There is one EMTFOutput for each MTF7 (60 deg. sector) in the event
	EMTFOutputCollection* res;
	res = static_cast<EMTFCollections*>(coll)->getEMTFOutputs();
	int iOut = res->size() - 1;

	////////////////////////////
	// Unpack the ME Data Record
	////////////////////////////

	l1t::emtf::ME ME_;

	ME_.set_clct_pattern        ( GetHexBits(MEa,  0,  3) );
	ME_.set_quality             ( GetHexBits(MEa,  4,  7) );
	ME_.set_key_wire_group      ( GetHexBits(MEa,  8, 14) );

	ME_.set_clct_key_half_strip ( GetHexBits(MEb,  0,  7) );
	ME_.set_csc_ID              ( GetHexBits(MEb,  8, 11) );
	ME_.set_lr                  ( GetHexBits(MEb, 12, 12) );
	ME_.set_bxe                 ( GetHexBits(MEb, 13, 13) );
	ME_.set_bc0                 ( GetHexBits(MEb, 14, 14) );

	ME_.set_me_bxn              ( GetHexBits(MEc,  0, 11) );
	ME_.set_nit                 ( GetHexBits(MEc, 12, 12) );
	ME_.set_cik                 ( GetHexBits(MEc, 13, 13) );
	ME_.set_afff                ( GetHexBits(MEc, 14, 14) );

	ME_.set_tbin_num            ( GetHexBits(MEd,  0,  2) );
	ME_.set_vp                  ( GetHexBits(MEd,  3,  3) );
	ME_.set_station             ( GetHexBits(MEd,  4,  6) );
	ME_.set_af                  ( GetHexBits(MEd,  7,  7) );
	ME_.set_epc                 ( GetHexBits(MEd,  8, 11) );
	ME_.set_sm                  ( GetHexBits(MEd, 12, 12) );
	ME_.set_se                  ( GetHexBits(MEd, 13, 13) );
	ME_.set_afef                ( GetHexBits(MEd, 14, 14) );

	// ME_.set_dataword            ( uint64_t dataword);

	(res->at(iOut)).push_ME(ME_);

	// Finished with unpacking one ME Data Record
	return true;
	
      } // End bool MEBlockUnpacker::unpack

      // bool MEBlockPacker::pack(const Block& block, UnpackerCollections *coll) {
      // 	std::cout << "Inside MEBlockPacker::pack" << std::endl;
      // 	return true;
      // } // End bool MEBlockPacker::pack

    } // End namespace emtf
  } // End namespace stage2
} // End namespace l1t

DEFINE_L1T_UNPACKER(l1t::stage2::emtf::MEBlockUnpacker);
// DEFINE_L1T_PACKER(l1t::stage2::MEBlockPacker);
