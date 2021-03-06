// Copyright (c) 2016-2018 The LoMoCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "config.h"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string/trim.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <iostream>

using namespace std;
using namespace walleve;

namespace po = boost::program_options;
namespace fs = boost::filesystem;

//////////////////////////////
// CWalleveConfig

CWalleveConfig::CWalleveConfig()
: defaultDesc("WalleveOptions"), ignoreCmd(0)
{
}

CWalleveConfig::~CWalleveConfig()
{
}

bool CWalleveConfig::Load(int argc,char *argv[],const fs::path& pathDefault,const string& strConfile)
{
    const int defaultCmdStyle = po::command_line_style::allow_long 
                         | po::command_line_style::long_allow_adjacent
                         | po::command_line_style::allow_long_disguise;
    fs::path pathConfile;
    try
    { 
        vector<string> vecIgnoreCmd;

        defaultDesc.add_options()
        ("cmd", po::value<vector<string> >(&vecCommand))
        ("help", po::value<bool>(&fHelp)->default_value(false))
        ("daemon", po::value<bool>(&fDaemon)->default_value(false))
        ("debug", po::value<bool>(&fDebug)->default_value(false))
        ("datadir", po::value<fs::path>(&pathRoot)->default_value(pathDefault))
        ("conf", po::value<fs::path>(&pathConfile)->default_value(fs::path(strConfile)))
        ("ignore", po::value<vector<string> >(&vecIgnoreCmd));

        po::positional_options_description defaultPosDesc;
        defaultPosDesc.add("cmd",-1).add("ignore", ignoreCmd);

        auto parser = po::command_line_parser(argc, argv).options(defaultDesc).style(defaultCmdStyle)
                .extra_parser(CWalleveConfig::ExtraParser)
                .positional(defaultPosDesc);
        po::store(parser.run(),vm);

        po::notify(vm);
        
        if (fHelp)
        {
            return true;
        }

        if (!pathConfile.is_complete())
        {
            pathConfile = pathRoot / pathConfile;
        }

        vector<string> confToken;
        if (TokenizeConfile(pathConfile.string().c_str(),confToken))
        {
            po::store(po::command_line_parser(confToken).options(defaultDesc).style(defaultCmdStyle)
                      .allow_unregistered().extra_parser(CWalleveConfig::ExtraParser).run(),vm);
            po::notify(vm);
        }
    }
    catch (exception& e)
    {
        cout << e.what() << std::endl;
        return false;
    }
    return true;
}

bool CWalleveConfig::PostLoad()
{
    pathData = pathRoot; 
    return true;
}

string CWalleveConfig::ListConfig() const
{
    ostringstream oss;
    oss << "debug : " << (fDebug ? "Y" : "N") << "\n"
        << "data path : " << pathData << "\n";
    return oss.str();
}

string CWalleveConfig::Help() const
{
    return string()
        + "  -help                         Get more information\n"
        + "  -daemon                       Run server in background\n"
        + "  -debug                        Run in debug mode\n"
        + "  -datadir                      Root directory of resources\n"
        + "  -conf                         Configuration file name\n";
}

pair<string,string> CWalleveConfig::ExtraParser(const string& s)
{
    if (s[0] == '-' && !isdigit(s[1]))
    {
        bool fRev = (s.substr(1,2) == "no");
        size_t eq = s.find('=');
        if (eq == string::npos)
        {
            if (fRev)
            {
                return make_pair(s.substr(3),string("0"));
            }
            else
            {
                return make_pair(s.substr(1),string("1"));
            }
        }
        else if (fRev)
        {
            int v = atoi(s.substr(eq+1).c_str());
            return make_pair(s.substr(3,eq-3),string(v != 0 ? "0" : "1"));
        }
    }
    return make_pair(string(), string());
}

void CWalleveConfig::AddOptions(boost::program_options::options_description& desc)
{
    defaultDesc.add(desc);
}

bool CWalleveConfig::TokenizeConfile(const char *pzConfile,vector<string>& tokens)
{
    ifstream ifs(pzConfile);
    if (!ifs)
    {
        return false;
    }
    string line;
    while(!getline(ifs,line).eof())
    {
        string s = line.substr(0,line.find('#'));
        boost::trim(s);
        if (!s.empty())
        {
            tokens.push_back(string("-") + s);
        }
    }

    return true;
}

void CWalleveConfig::SetIgnoreCmd(int number)
{
    ignoreCmd = number;
}

vector<string> CWalleveConfig::ParseCmd(int argc, char* argv[])
{
    vector<string> vecCmd;

    po::options_description desc;
    desc.add_options()("cmd", po::value<vector<string> >(&vecCmd));

    po::positional_options_description optDesc;
    optDesc.add("cmd", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc)
                                                 .allow_unregistered()
                                                 .positional(optDesc)
                                                 .run(), vm);
    po::notify(vm);
    return vecCmd;
}

