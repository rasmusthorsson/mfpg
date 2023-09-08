// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/elements/WedgeAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( WedgeAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Wedge )

        inline WedgePtr makeWedge() { return std::make_shared<Wedge>(); }

        class Wedge : public ElementInterface
        {
        public:
            Wedge();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            WedgeAttributesPtr getAttributes() const;
            void setAttributes( const WedgeAttributesPtr& attributes );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            WedgeAttributesPtr myAttributes;
        };
    }
}
