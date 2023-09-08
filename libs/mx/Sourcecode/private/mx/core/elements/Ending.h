// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/XsString.h"
#include "mx/core/elements/EndingAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( EndingAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Ending )

        inline EndingPtr makeEnding() { return std::make_shared<Ending>(); }
		inline EndingPtr makeEnding( const XsString& value ) { return std::make_shared<Ending>( value ); }
		inline EndingPtr makeEnding( XsString&& value ) { return std::make_shared<Ending>( std::move( value ) ); }

        class Ending : public ElementInterface
        {
        public:
            Ending();
            Ending( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            EndingAttributesPtr getAttributes() const;
            void setAttributes( const EndingAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            XsString myValue;
            EndingAttributesPtr myAttributes;
        };
    }
}
