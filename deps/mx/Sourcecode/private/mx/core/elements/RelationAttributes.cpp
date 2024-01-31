// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/elements/RelationAttributes.h"
#include "mx/core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        RelationAttributes::RelationAttributes()
        :type()
        ,hasType( false )
        {}


        bool RelationAttributes::hasValues() const
        {
            return hasType;
        }


        std::ostream& RelationAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, type, "type", hasType );
            }
            return os;
        }


        bool RelationAttributes::fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement )
        {
            const char* const className = "RelationAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, type, hasType, "type" ) ) { continue; }
            }
        
        
            return isSuccess;
        }

    }
}
