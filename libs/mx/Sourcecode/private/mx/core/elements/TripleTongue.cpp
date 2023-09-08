// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/elements/TripleTongue.h"
#include "mx/core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        TripleTongue::TripleTongue()
        :ElementInterface()
        ,myAttributes( std::make_shared<EmptyPlacementAttributes>() )
        {}


        bool TripleTongue::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool TripleTongue::hasContents() const  { return false; }
        std::ostream& TripleTongue::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& TripleTongue::streamName( std::ostream& os ) const  { os << "triple-tongue"; return os; }
        std::ostream& TripleTongue::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        EmptyPlacementAttributesPtr TripleTongue::getAttributes() const
        {
            return myAttributes;
        }


        void TripleTongue::setAttributes( const EmptyPlacementAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool TripleTongue::fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
