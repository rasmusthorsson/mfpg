// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/PositiveIntegerOrEmpty.h"
#include "mx/core/elements/MultipleRestAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( MultipleRestAttributes )
        MX_FORWARD_DECLARE_ELEMENT( MultipleRest )

        inline MultipleRestPtr makeMultipleRest() { return std::make_shared<MultipleRest>(); }
		inline MultipleRestPtr makeMultipleRest( const PositiveIntegerOrEmpty& value ) { return std::make_shared<MultipleRest>( value ); }
		inline MultipleRestPtr makeMultipleRest( PositiveIntegerOrEmpty&& value ) { return std::make_shared<MultipleRest>( std::move( value ) ); }

        class MultipleRest : public ElementInterface
        {
        public:
            MultipleRest();
            MultipleRest( const PositiveIntegerOrEmpty& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MultipleRestAttributesPtr getAttributes() const;
            void setAttributes( const MultipleRestAttributesPtr& attributes );
            PositiveIntegerOrEmpty getValue() const;
            void setValue( const PositiveIntegerOrEmpty& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            PositiveIntegerOrEmpty myValue;
            MultipleRestAttributesPtr myAttributes;
        };
    }
}
