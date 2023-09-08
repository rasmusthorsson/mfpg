// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/AttributesInterface.h"
#include "mx/core/CommaSeparatedText.h"
#include "mx/core/Enums.h"
#include "mx/core/FontSize.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( TupletNumberAttributes )

        struct TupletNumberAttributes : public AttributesInterface
        {
        public:
            TupletNumberAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            CommaSeparatedText fontFamily;
            FontStyle fontStyle;
            FontSize fontSize;
            FontWeight fontWeight;
            bool hasFontFamily;
            bool hasFontStyle;
            bool hasFontSize;
            bool hasFontWeight;

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );
        };
    }
}
