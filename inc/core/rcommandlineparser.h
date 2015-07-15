
#ifndef RCOMMANDLINEPARSER_H
#define RCOMMANDLINEPARSER_H

#include <vector>
#include <string>
#include <exception>

namespace chikkooos
{

class RCommandLineParser
{
private:
    class Options
    {
    public:
        Options()
         : mHasArgument(false)
        {}
        Options(std::string o, bool a)
         : mOption(o),
           mHasArgument(a)
        {}

        std::string mOption;
        std::string mArgument;
        bool mHasArgument;
    };

    typedef std::vector<Options> OptionsRVector;
    typedef OptionsRVector::iterator OptionsRVectorIter;
    typedef OptionsRVector::const_iterator OptionsRVectorConstIter;

public:
    RCommandLineParser()
    {}
    RCommandLineParser(std::string const & options)
    {
        setOptions(options);
    }

    void addOption(std::string opt, bool hasArg=false)
    {
        if (!opt.empty()) {
            std::string option;
            if (opt[0] == '-') {
                option = opt;
            } else {
                if (opt.size() == 1) {
                    option.append(1, '-');
                    option.append(opt);
                } else {
                    option.append(2, '-');
                    option.append(opt);
                }
            }
            if (!hasOption(option)) {
                mOptions.push_back(Options(option, hasArg));
            }
        }
    }

    bool hasOption(std::string const & option)
    {
        return getOption(option) != 0;
    }

    bool hasArgument(std::string const & option)
    {
        Options * optData = getOption(option);
        if (optData && optData->mHasArgument) {
            return true;
        }
        return false;
    }

    class Exception: std::exception
    {
    public:
        enum Error
        {
        NoError,
        InvalidOption,
        ArgumentMissing
        };
    
    public:
        Exception(std::string const & m, Error e)
         : mMessage(m),
           mErrorCode(e)
        {}

        ~Exception() throw()
        {}

        const char* what() const throw()
        {
            return mMessage.c_str();
        }

        Error errorCode() const
        {
            return mErrorCode;
        }

    private:
        std::string mMessage;
        Error mErrorCode;
    };

    class Iterator
    {
    public:
        class OptionPair
        {
        public:
            std::string option;
            std::string argument;

        public:
            void clear()
            {
                option.clear();
                argument.clear();
            }
            void set(std::string const &o)
            {
                option = o;
            }
            void set(std::string const &o, std::string const &a)
            {
                option = o;
                argument = a;
            }
        };

    public:
        Iterator(RCommandLineParser * parser, int argc=0, const char ** argv=0)
         : mParser(parser),
           mArgc(argc),
           mArgv(argv),
           mIndex(0)
        {
            next();
        }

        Iterator(const Iterator & oth)
        {
            mParser = oth.mParser;
            mArgc = oth.mArgc;
            mArgv = oth.mArgv;
            mIndex = oth.mIndex;
            mOption = oth.mOption;
        }

        Iterator& operator=(const Iterator & oth)
        {
            if (this != &oth) {
                mParser = oth.mParser;
                mArgc = oth.mArgc;
                mArgv = oth.mArgv;
                mIndex = oth.mIndex;
                mOption = oth.mOption;
            }
            return *this;
        }

        bool operator==(Iterator const &oth)
        {
            return this->mParser == oth.mParser &&
                   this->mIndex  == oth.mIndex &&
                   this->mArgc == oth.mArgc &&
                   this->mArgv == oth.mArgv;
        }

        bool operator!=(Iterator const &oth)
        {
            return !(*this == oth);
        }

        Iterator operator++(int)
        {
            Iterator iter(*this);
            ++(*this);
            return iter;
        }

        Iterator& operator++()
        {
            next();
            return *this;
        }

        void next()
        {
            mOption.clear();
            if (mIndex >= mArgc) {
                mIndex = 0;
                mArgc = 0;
                mArgv = 0;
                return;
            }

            std::string option(mArgv[mIndex]);
            std::string argument;

            RCommandLineParser::Options *optionData = mParser->getOption(option);
            while (true) {
                if (optionData) {
                    if (optionData->mHasArgument) {
                        if (mIndex+1 < mArgc) {
                            argument = mArgv[++mIndex];
                        } else {
                            throw RCommandLineParser::Exception(std::string("argument missing"), 
                                    RCommandLineParser::Exception::ArgumentMissing);
                        }
                    }
                    mOption.set(option, argument);
                    ++mIndex;
                    break;
                } else {
                    ++mIndex;
                    if (mIndex >= mArgc) {
                        mIndex = 0;
                        mArgc = 0;
                        mArgv = 0;
                        break;
                    }
                }
                option = std::string(mArgv[mIndex]);
                optionData = mParser->getOption(option);
            }

        }

        const OptionPair * operator->() const
        {
            return &mOption;
        }

    private:
        RCommandLineParser * mParser;
        int mArgc;
        const char ** mArgv;
        int mIndex;
        OptionPair mOption;
    };

    Iterator begin(int argc, const char ** argv)
    {
        return Iterator(this, argc, argv);
    }

    Iterator end()
    {
        return Iterator(this);
    }

private:
    void setOptions(std::string const & options)
    {
        std::size_t length = options.length();   

        for (std::size_t i=0; i<length; ++i) {
            std::string option = options.substr(i, 1);
            if (options.length() > i+1 && options[i+1] == ':') {
                addOption(option, true);
            } else {
                addOption(option, false);
            }
        }
    }

    Options * getOption(std::string const &option)
    {
        Options * optionData = 0;
        for (OptionsRVectorIter iter = mOptions.begin();
             iter != mOptions.end(); ++iter) {
            if (option == iter->mOption) {
                optionData = &(*iter);
                break;
            }
        }
        return optionData;
    }

private:
    OptionsRVector mOptions;
};

}

#endif

