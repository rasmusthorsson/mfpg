// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/elements/Schleifer.h"
#include "mx/core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Schleifer::Schleifer()
        :ElementInterface()
        ,myAttributes( std::make_shared<EmptyPlacementAttributes>() )
        {}


        bool Schleifer::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Schleifer::hasContents() const  { return false; }
        std::ostream& Schleifer::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Schleifer::streamName( std::ostream& os ) const  { os << "schleifer"; return os; }
        std::ostream& Schleifer::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        EmptyPlacementAttributesPtr Schleifer::getAttributes() const
        {
            return myAttributes;
        }


        void Schleifer::setAttributes( const EmptyPlacementAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Schleifer::fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
