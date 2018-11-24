// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The LFN Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "uint256.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000d735f1eaa3f868ca4a644d67d054fb64da8f9e748d029ce9db680c34da5"))
    (49,uint256("0x00008dc5d9fe79240273e72ac10f7f1d3c8a5a0bc59b2336e15ec8c57cafbab4"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1543024073, // * UNIX timestamp of last checkpoint block
    50,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xff;
        pchMessageStart[3] = 0xf1;
        vAlertPubKey = ParseHex("043635a66ad599a93face6d23f09c96d2a17d18771ab70538862232aaacb5fe07087e016e5cd935478308e45cc533b4a98739d84a0aa8e7017633347909280b1a9");
        nDefaultPort = 6104;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 30;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nMaturity = 30;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 25009988 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 240;
        nModifierUpdateBlock = 1; // we use the version 2 for LFN

        const char* pszTimestamp = "Nov 23rd 2018, Trump again threatens to close southern border";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e5a8143f86ad8ac63791fbbdb8e5b91a8da88c8c693a95f6c2c13c063ea790f7960b8025a9047a7bc671d5cfe707a2dd2e13b86182e1064a0eea7bf863636363") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1542970105;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 574108;
        hashGenesisBlock = genesis.GetHash();

        /*uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        while (genesis.GetHash() > hashTarget)
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
                printf("nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }

        hashGenesisBlock = genesis.GetHash();
        printf("MN nNonce %u\n", genesis.nNonce);
        printf("MN hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
        printf("MN hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("MN nTime %u\n", genesis.nTime);
        */

        assert(hashGenesisBlock == uint256("0x00000d735f1eaa3f868ca4a644d67d054fb64da8f9e748d029ce9db680c34da5"));
        assert(genesis.hashMerkleRoot == uint256("0x1aa21386a5935fd7d69d2706f8fb35651994f6b8adbd8db52a206ec327895e64"));

        // DNS Seeding
        vSeeds.clear();
        vFixedSeeds.clear();
        vSeeds.push_back(CDNSSeedData("lfn-seed-1.dynu.net", "lfn-seed-1.dynu.net"));
        vSeeds.push_back(CDNSSeedData("lfn-seed-2.dynu.net", "lfn-seed-2.dynu.net"));
        vSeeds.push_back(CDNSSeedData("lfn-seed-3.dynu.net", "lfn-seed-3.dynu.net"));
        vSeeds.push_back(CDNSSeedData("lfn-seed-4.dynu.net", "lfn-seed-4.dynu.net"));
        vSeeds.push_back(CDNSSeedData("lfn-seed-5.dynu.net", "lfn-seed-5.dynu.net"));

        // LFN coin addresses start with 'L'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 48);
        // LFN coin script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
        // LFN coin private keys start with 'K'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
        // LFN coin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // LFN coin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // LFN coin BIP44 coin type is '222' (0x800000de)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "043635a66ad599a93face6d23f09c96d2a17d18771ab70538862232aaacb5fe07087e016e5cd935478308e45cc533b4a98739d84a0aa8e7017633347909280b1a9";
        strMasternodePoolDummyAddress = "LZyyFSCdDke6XE9jW8ZynBfKWuVpLuxPnh";
        nStartMasternodePayments = genesis.nTime;

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x46;
        pchMessageStart[1] = 0x77;
        pchMessageStart[2] = 0x66;
        pchMessageStart[3] = 0xbb;
        vAlertPubKey = ParseHex("041b2b4c86273359acac3522471911ed2b303eaab65e8a1de01c06e89f2eab1e55234a4b504f3ce20c6f661f007d0ca15623b4358d9855c7c8ba793a24fa315e22");
        nDefaultPort = 11711;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nLastPOWBlock = 120;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 40000000 * COIN;


        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1542970105;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 574108;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000d735f1eaa3f868ca4a644d67d054fb64da8f9e748d029ce9db680c34da5"));
        assert(genesis.hashMerkleRoot == uint256("0x1aa21386a5935fd7d69d2706f8fb35651994f6b8adbd8db52a206ec327895e64"));

        /*uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        while (genesis.GetHash() > hashTarget)
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
                printf("nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }


        hashGenesisBlock = genesis.GetHash();
        printf("TN nNonce %u\n", genesis.nNonce);
        printf("TN hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
        printf("TN hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("TN nTime %u\n", genesis.nTime);
        */

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet LFN coin addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 98);
        // Testnet LFN coin script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet LFN coin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet LFN coin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet LFN Core BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04abb5e65280dda6a113fadfb9877f9c399532245fe1acb61de293ab298034d5084277fab3768774a3b68cbbe5021cc5049ec8c9997a13f64da1afa0bcfb156db1";
        strMasternodePoolDummyAddress = "gbJ4Qad4xc77PpLzMx6rUegAs6aUPWkcUq";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7f;
        pchMessageStart[3] = 0xad;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 1.5 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1542970105;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 574108;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 11721;
        /*uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        while (genesis.GetHash() > hashTarget)
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
                printf("nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }

        hashGenesisBlock = genesis.GetHash();
        printf("RT nNonce %u\n", genesis.nNonce);
        printf("RT hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
        printf("RT hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("RT nTime %u\n", genesis.nTime);
        */

        assert(hashGenesisBlock == uint256("0x00000d735f1eaa3f868ca4a644d67d054fb64da8f9e748d029ce9db680c34da5"));
        assert(genesis.hashMerkleRoot == uint256("0x1aa21386a5935fd7d69d2706f8fb35651994f6b8adbd8db52a206ec327895e64"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 11731;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
