#pragma once
#include <FlexLexer.h>
#include "grammar.tab.hh"

namespace yy {

class Driver {
    FlexLexer *plex_;
};

}