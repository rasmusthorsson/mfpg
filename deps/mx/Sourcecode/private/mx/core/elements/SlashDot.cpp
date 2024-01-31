// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/elements/SlashDot.h"
#include "mx/core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        SlashDot::SlashDot() : ElementInterface() {}


        bool SlashDot::hasAttributes() const { return false; }


        bool SlashDot::hasContents() const  { return false; }
        std::ostream& SlashDot::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& SlashDot::streamName( std::ostream& os ) const  { os << "slash-dot"; return os; }
        std::ostream& SlashDot::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool SlashDot::fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
