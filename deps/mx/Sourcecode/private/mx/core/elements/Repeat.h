// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/elements/RepeatAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( RepeatAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Repeat )

        inline RepeatPtr makeRepeat() { return std::make_shared<Repeat>(); }

        class Repeat : public ElementInterface
        {
        public:
            Repeat();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            RepeatAttributesPtr getAttributes() const;
            void setAttributes( const RepeatAttributesPtr& attributes );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            RepeatAttributesPtr myAttributes;
        };
    }
}
