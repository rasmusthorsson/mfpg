// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/elements/BarreAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( BarreAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Barre )

        inline BarrePtr makeBarre() { return std::make_shared<Barre>(); }

        class Barre : public ElementInterface
        {
        public:
            Barre();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            BarreAttributesPtr getAttributes() const;
            void setAttributes( const BarreAttributesPtr& attributes );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            BarreAttributesPtr myAttributes;
        };
    }
}
