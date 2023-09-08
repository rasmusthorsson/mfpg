// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/elements/NotationsAttributes.h"
#include "mx/core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        NotationsAttributes::NotationsAttributes()
        :printObject( YesNo::no )
        ,hasPrintObject( false )
        {}


        bool NotationsAttributes::hasValues() const
        {
            return hasPrintObject;
        }


        std::ostream& NotationsAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, printObject, "print-object", hasPrintObject );
            }
            return os;
        }


        bool NotationsAttributes::fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement )
        {
            const char* const className = "NotationsAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, printObject, hasPrintObject, "print-object", &parseYesNo ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
