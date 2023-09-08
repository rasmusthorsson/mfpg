// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/AttributesInterface.h"
#include "mx/core/Integers.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( AccordAttributes )

        struct AccordAttributes : public AttributesInterface
        {
        public:
            AccordAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            StringNumber string;
            bool hasString;

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );
        };
    }
}
