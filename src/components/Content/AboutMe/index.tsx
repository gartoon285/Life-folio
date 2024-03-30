import { styled, Box } from "@mui/material";
import MyImage from "../../../assets/pict.jpg";
import Resume from "../../../assets/resume.pdf";
import {
  CustomButton,
  SectionWrapper,
  TitleWrapper,
} from "../../../styles/sectionStyles";
import { useEffect } from "react";
const AboutMeContainer = styled(Box)(({ theme }) => ({
  display: "flex",
  alignSelf: "center",
  "& img": {
    width: 400,
    [theme.breakpoints.down("sm")]: {
      width: 350,
    },
  },
  [theme.breakpoints.down("md")]: {
    flexDirection: "column",
  },
}));

const DetailsWrapper = styled(Box)(({ theme }) => ({
  fontSize: 16,
  marginLeft: 15,
  "& .actions": {
    margin: "12px 0",
  },
  [theme.breakpoints.down("md")]: {
    margin: "10px 0 0 0",
  },
}));
export const AboutMe = () => {
  useEffect(() => {
    window.scrollTo(0, 0);
  }, []);

  return (
    <SectionWrapper>
      <TitleWrapper>About Me</TitleWrapper>
      <AboutMeContainer>
        <img src={MyImage} />
        <DetailsWrapper>
          <div>
          I’m Sathaporn Bunyiseng. I’m interested in IoT or Microcontroller. I started writing code to control Microcontroller since 2015. <br/>In 2018 I got honorable mention in a project competition using Microcontroller.
          Present I’m doing a project about Microcontroller to control Robot.
          </div>
          <div className="actions">
            <CustomButton>
              <a href={Resume} rel="noreferrer" target="_blank">
                View Resume
              </a>
            </CustomButton>
          </div>
        </DetailsWrapper>
      </AboutMeContainer>
    </SectionWrapper>
  );
};
