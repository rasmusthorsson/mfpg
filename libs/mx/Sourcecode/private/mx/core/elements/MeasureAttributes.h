// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/AttributesInterface.h"
#include "mx/core/Decimals.h"
#include "mx/core/Enums.h"
#include "mx/core/XsToken.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {
        MX_FORWARD_DECLARE_ATTRIBUTES( MeasureAttributes )

        struct MeasureAttributes : public AttributesInterface
        {
        public:
            MeasureAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            XsToken number;
            YesNo implicit;
            YesNo nonControlling;
            TenthsValue width;
            const bool hasNumber;
            bool hasImplicit;
            bool hasNonControlling;
            bool hasWidth;

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );
        };
    }
}
