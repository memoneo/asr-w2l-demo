#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController
{
public:
    /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
    MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {
    }

public:
    ENDPOINT("GET", "/", root)
    {
        auto dto = SttResponseDto::createShared();
        dto->statusCode = 200;
        dto->message = "OK";
        dto->text = "-";
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(stt)
    {
        info->summary = "STT";

        info->addConsumes<Object<SttRequestDto>>("application/json");

        info->addResponse<Object<SttResponseDto>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("POST", "/stt", stt, BODY_DTO(Object<SttRequestDto>, requestDto))
    {
        auto dto = SttResponseDto::createShared();
        dto->statusCode = 200;
        dto->message = "OK";
        dto->text = requestDto->encoded;
        return createDtoResponse(Status::CODE_200, dto);
    }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
