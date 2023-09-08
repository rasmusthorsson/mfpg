// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/AttributesInterface.h"
#include "mx/core/Decimals.h"
#include "mx/core/Enums.h"
#include "mx/core/Integers.h"
#include "mx/core/XlinkHref.h"
#include "mx/core/XlinkRole.h"
#include "mx/core/XlinkTitle.h"
#include "mx/core/XsNMToken.h"
#include "mx/core/XsToken.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( LinkAttributes )

        struct LinkAttributes : public AttributesInterface
        {
        public:
            LinkAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            XlinkHref href;
            const XlinkType type;
            XlinkRole role;
            XlinkTitle title;
            XlinkShow show;
            XlinkActuate actuate;
            XsToken name;
            XsNMToken element;
            PositiveInteger position;
            TenthsValue defaultX;
            TenthsValue defaultY;
            TenthsValue relativeX;
            TenthsValue relativeY;
            const bool hasHref;
            bool hasType;
            bool hasRole;
            bool hasTitle;
            bool hasShow;
            bool hasActuate;
            bool hasName;
            bool hasElement;
            bool hasPosition;
            bool hasDefaultX;
            bool hasDefaultY;
            bool hasRelativeX;
            bool hasRelativeY;

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );
        };
    }
}
