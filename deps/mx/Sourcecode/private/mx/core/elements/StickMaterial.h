// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/Enums.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( StickMaterial )

        inline StickMaterialPtr makeStickMaterial() { return std::make_shared<StickMaterial>(); }
		inline StickMaterialPtr makeStickMaterial( const StickMaterialEnum& value ) { return std::make_shared<StickMaterial>( value ); }
		inline StickMaterialPtr makeStickMaterial( StickMaterialEnum&& value ) { return std::make_shared<StickMaterial>( std::move( value ) ); }

        class StickMaterial : public ElementInterface
        {
        public:
            StickMaterial();
            StickMaterial( const StickMaterialEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StickMaterialEnum getValue() const;
            void setValue( const StickMaterialEnum& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            StickMaterialEnum myValue;
        };
    }
}
