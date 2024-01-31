// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/ElementInterface.h"
#include "ezxml/XElement.h"
#include "ezxml/XElementIterator.h"
#include "ezxml/XFactory.h"
#include <sstream>

namespace mx
{
    namespace core
    {
        const char* INDENT = "   ";
 
        ElementInterface::ElementInterface()
        {

        }
        
        ElementInterface::~ElementInterface()
        {

        }
        
        
        std::ostream& ElementInterface::streamOpenTag( std::ostream& os ) const
        {
            os << "<";
            this->streamName( os );
            if ( hasAttributes() )
            {
                streamAttributes( os );
            }
            os << ">";
            return os;
        }


        std::ostream& ElementInterface::streamCloseTag( std::ostream& os ) const
        {
            os << "</";
            this->streamName( os );
            os << ">";
            return os;
        }


        std::ostream& ElementInterface::streamSelfCloseTag( std::ostream& os ) const
        {
            os << "<";
            this->streamName( os );
            if ( hasAttributes() )
            {
                streamAttributes( os );
            }
            os << "/>";
            return os;
        }
        bool ElementInterface::hasContents() const
        {
            std::stringstream ss;
            bool discard;
            streamContents( ss, 0, discard );
            return ( ss.str() ).length() > 0;
        }


        std::ostream& ElementInterface::toStream( std::ostream& os, const int indentLevel ) const
        {
            indent( os, indentLevel );

            if( myProcessingInstructions.empty() )
            {
                return streamWithoutProcessingInstructions( os, indentLevel );
            }
            else
            {
                std::stringstream ss;
                streamWithoutProcessingInstructions( ss, 0 );
                const auto xml = ss.str();
                std::istringstream iss{ xml };
                const auto xdoc = ::ezxml::XFactory::makeXDoc();
                xdoc->loadStream( iss );
                const auto root = xdoc->getRoot();
                const bool hasChildren = root->getType() == ::ezxml::XElementType::element && root->begin() != root->end();
                streamWithProcessingInstructions( os, indentLevel, hasChildren );
            }

            return os;
        }
        
        
        const std::string ElementInterface::getElementName() const
        {
            std::stringstream ss;
            this->streamName( ss );
            return ss.str();
        }


        std::ostream& indent( std::ostream& os, const int indentLevel )
        {
            for ( int i = 0; i < indentLevel; ++i )
            {
                os << INDENT;
            }
            return os;
        }
        
        
        bool ElementInterface::hasAttributes() const
        {
            return false;
        }


        bool ElementInterface::fromXElement( std::ostream& message, ::ezxml::XElement& xelement )
        {
            if( xelement.getIsProcessingInstruction() )
            {
                const auto next = xelement.getNextSibling();

                if( next )
                {
                    return this->fromXElement( message, *next );
                }
            }
            
            const bool result = this->fromXElementImpl( message, xelement );

            // check for processing instructions

            if( xelement.getType() == ezxml::XElementType::element )
            {
                auto childIter = xelement.beginWithProcessingInstructions();
                const auto childEnd = xelement.end();

                while( childIter != childEnd && childIter->getIsProcessingInstruction() )
                {
                    // inexplicably, the following line caused a bad address crash on msvc
                    // ProcessingInstruction pi{ childIter->getName(), childIter->getValue() };
                    // surely this is an msvc compiler bug? prove me wrong. anyway, we store
                    // the getName() and getValue() results in short-lived variables to work
                    // around the windows issue.
                    auto name = childIter->getName();
                    auto value = childIter->getValue();
                    ProcessingInstruction pi{ name, value };
                    pi.setIsChild( true );
                    addProcessingInstruction( std::move( pi ) );
                    ++childIter;
                }
            }

            auto lookahead = xelement.getNextSibling();

            while( lookahead != nullptr && lookahead->getIsProcessingInstruction() )
            {
                ProcessingInstruction pi{ lookahead->getName(), lookahead->getValue() };
                pi.setIsChild( false );
                addProcessingInstruction( std::move( pi ) );
                lookahead = lookahead->getNextSibling();
            }

            return result;
        }


        const ProcessingInstructions& ElementInterface::getProcessingInstructions() const
        {
            return myProcessingInstructions;
        }


        void ElementInterface::clearProcessingInstructions()
        {
            myProcessingInstructions.clear();
        }


        void ElementInterface::addProcessingInstruction( ProcessingInstruction inProcessingInstruction )
        {
            myProcessingInstructions.emplace_back( std::move( inProcessingInstruction ) );
        }


        std::ostream& operator<<( std::ostream& os, const ElementInterface& value )
        {
            return value.toStream( os, 0 );
        }


        std::ostream& ElementInterface::writeChildProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            bool isFirst = true;

            for( const auto& pi : myProcessingInstructions )
            {
                if( pi.getIsChild() )
                {
                    if (!isFirst)
                    {
                        os << std::endl;
                    }
                    indent( os, indentLevel + 1 );
                    pi.toStream( os );
                    isFirst = false;
                }
            }

            return os;
        }


        std::ostream& ElementInterface::writeSiblingProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            bool isFirst = true;

            for( const auto& pi : myProcessingInstructions )
            {
                if( !pi.getIsChild() )
                {
                    if (!isFirst)
                    {
                        os << std::endl;
                    }
                    indent( os, indentLevel );
                    pi.toStream( os );
                    isFirst = false;
                }
            }

            return os;
        }


        std::ostream& ElementInterface::writeAllProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            bool isFirst = true;

            for( const auto& pi : myProcessingInstructions )
            {
                if (!isFirst)
                {
                    os << std::endl;
                }
                indent( os, indentLevel );
                pi.toStream( os );
                isFirst = false;
            }

            return os;
        }


        std::ostream& ElementInterface::streamWithoutProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            const bool isSelfClosing = !hasContents();

            if ( !isSelfClosing )
            {
                streamOpenTag( os );
                bool isOneLineOnly = false;
                streamContents( os, indentLevel, isOneLineOnly );
                if ( !isOneLineOnly )
                {
                    indent( os, indentLevel );
                }
                streamCloseTag( os );
            }
            else
            {
                streamSelfCloseTag( os );
            }
            return os;
        }


        std::ostream& ElementInterface::streamWithProcessingInstructions( std::ostream& os, const int indentLevel, const bool inHasChildren ) const
        {
            const bool isSelfClosing = !hasContents();

            if ( !isSelfClosing )
            {
                streamOpenTag( os );
                bool isOneLineOnly = false;

                if( inHasChildren )
                {
                    writeChildProcessingInstructions( os, indentLevel );
                }

                streamContents( os, indentLevel, isOneLineOnly );

                if ( !isOneLineOnly )
                {
                    indent( os, indentLevel );
                }
                streamCloseTag( os );

                if( inHasChildren )
                {
                    os << std::endl;
                    writeSiblingProcessingInstructions( os, indentLevel );
                }
                else
                {
                    os << std::endl;
                    writeAllProcessingInstructions( os, indentLevel );
                }
            }
            else
            {
                streamSelfCloseTag( os );
                os << std::endl;
                writeAllProcessingInstructions( os, indentLevel );
            }
            return os;
        }
    }
}
