#pragma once

#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Common/BitVector.h>
#include <cryptoTools/Common/Matrix.h>
#include <cryptoTools/Crypto/PRNG.h>
#include <cryptoTools/Network/Channel.h>

namespace osuCrypto
{
    class BgicksMultiPprfSender
    {
    public:
        u64 mDomain = 0, mDepth = 0, mPntCount = 0, mPntCount8;
        block mValue;
        
        
        std::vector<block> mBuffer;

        Matrix<std::array<block, 2>> mBaseOTs;

        BgicksMultiPprfSender() = default;
        BgicksMultiPprfSender(const BgicksMultiPprfSender&) = delete;
        BgicksMultiPprfSender(BgicksMultiPprfSender&&) = default;

        BgicksMultiPprfSender(u64 domainSize, u64 pointCount);

        void configure(u64 domainSize, u64 pointCount);

        
        // the number of base OTs that should be set.
        u64 baseOtCount() const;

        // returns true if the base OTs are currently set.
        bool hasBaseOts() const; 
        

        void setBase(span<std::array<block, 2>> baseMessages);

        // expand the whole PPRF and store the result in output
        void expand(Channel& chl, block value, PRNG& prng, MatrixView<block> output, bool transpose = false);


        void setValue(block value);

        // expand the next output.size() number of outputs and store the result in output.
        //void yeild(Channel& chl, PRNG& prng, span<block> output);

    };


    class BgicksMultiPprfReceiver
    {
    public:
        u64 mDomain = 0, mDepth = 0,  mPntCount = 0, mPntCount8;

        Matrix<block> mBaseOTs;
        Matrix<u8> mBaseChoices;


        BgicksMultiPprfReceiver() = default;
        BgicksMultiPprfReceiver(const BgicksMultiPprfReceiver&) = delete;
        BgicksMultiPprfReceiver(BgicksMultiPprfReceiver&&) = default;
        BgicksMultiPprfReceiver(u64 domainSize, u64 pointCount);

        void configure(u64 domainSize, u64 pointCount);


        // the number of base OTs that should be set.
        u64 baseOtCount() const;

        // returns true if the base OTs are currently set.
        bool hasBaseOts() const;


        void setBase(span<block> baseMessages, BitVector& choices);


        void getPoints(span<u64> points);
		void getTransposedPoints(span<u64> points);

        void expand(Channel& chl, PRNG& prng, MatrixView<block> output, bool transpose = false);


        //void setPoints(span<u64> points);

        //void yeild(Channel& chl, PRNG& prng, span<block> output);
    };
}