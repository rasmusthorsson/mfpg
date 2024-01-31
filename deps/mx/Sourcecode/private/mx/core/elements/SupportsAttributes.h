// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/AttributesInterface.h"
#include "mx/core/CommaSeparatedText.h"
#include "mx/core/Enums.h"
#include "mx/core/XsNMToken.h"
#include "mx/core/XsToken.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( SupportsAttributes )

        struct SupportsAttributes : public AttributesInterface
        {
        public:
            SupportsAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            YesNo type;
            XsNMToken element;
            XsNMToken attribute;
            XsToken value;
            const bool hasType;
            const bool hasElement;
            bool hasAttribute;
            bool hasValue;

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );
        };
    }
}
