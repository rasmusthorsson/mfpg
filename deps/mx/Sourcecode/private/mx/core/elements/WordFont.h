// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/elements/EmptyFontAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( EmptyFontAttributes )
        MX_FORWARD_DECLARE_ELEMENT( WordFont )

        inline WordFontPtr makeWordFont() { return std::make_shared<WordFont>(); }

        class WordFont : public ElementInterface
        {
        public:
            WordFont();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            EmptyFontAttributesPtr getAttributes() const;
            void setAttributes( const EmptyFontAttributesPtr& attributes );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            EmptyFontAttributesPtr myAttributes;
        };
    }
}
