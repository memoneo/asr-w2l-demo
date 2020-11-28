#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class SttResponseDto : public oatpp::DTO {
  
  DTO_INIT(SttResponseDto, DTO)
  
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
  DTO_FIELD(String, text);
  
};

class SttRequestDto : public oatpp::DTO {
  
  DTO_INIT(SttRequestDto, DTO)
  
  DTO_FIELD(String, encoded);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */